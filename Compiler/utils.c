#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "headers/utils.h"

#define NO_LABEL -1
#define True 1
#define False 0

static int tmp_counter = 0;

void print_reduce(char *left, char* right){
	FILE *output_file;

	assert(left != NULL);
	assert(right != NULL);

	output_file = fopen("syntax_rules.txt", "a");
	assert(output_file != NULL);

	fprintf(output_file, "%s -> %s\n", left, right);
	fclose(output_file);
}

Symbol* check_for_lib_func(SymTable_T oSymTable, char *name){
	
	Symbol* lib = SymTable_lookup_scope(oSymTable, name, 0);

        if(lib != NULL && strcmp(lib->type, "library function") == 0)
        	return lib;

	return NULL;
}

Symbol* new_tmp(SymTable_T oSymTable, int scope, int line){

	Symbol *tmp;
	char name[64];

	sprintf(name, "_t%d", tmp_counter);

	tmp = Symbol_create(name, "tmp variable", scope, line, 1, 1);

	SymTable_put(oSymTable, tmp);

	tmp_counter++;

	return tmp;	
}

void reset_tmps(){

	tmp_counter = 0;
}

Expr* emit_bool_expr(Expr *expr, SymTable_T sym_table, int current_scope, int line){

	Symbol *tmp;
	Expr *result;
	int true_assign_quad;
	int jump_quad;
	int false_assign_quad;

	if(expr == NULL)
		return NULL;

	if(expr->PendingTrueJumps == NULL && expr->PendingFalseJumps == NULL)
		return expr;

	tmp = new_tmp(sym_table, current_scope, line);
	result = lvalue_expr(tmp, boolexpr);

	true_assign_quad = get_quad_count();
	new_quad(_assign, result, bool_const_expr(True), NULL, NO_LABEL);

	jump_quad = get_quad_count();
	new_quad(_jump, NULL, NULL, NULL, NO_LABEL);

	false_assign_quad = get_quad_count();
	new_quad(_assign, result, bool_const_expr(False), NULL, NO_LABEL);

	fill_pending_labels_of_list(expr->PendingTrueJumps, true_assign_quad);
	fill_pending_labels_of_list(expr->PendingFalseJumps, false_assign_quad);
	fill_pending_label(jump_quad, get_quad_count());

	result->PendingTrueJumps = NULL;
	result->PendingFalseJumps = NULL;

	return result;
}

Expr* handle_comparison_quad(opcode op, Expr *arg1, Expr *arg2, SymTable_T sym_table, int current_scope, int line){

	Expr *expr = create_expr(boolexpr);
	Expr *left;
	Expr *right;

	left = emit_bool_expr(arg1, sym_table, current_scope, line);
	right = emit_bool_expr(arg2, sym_table, current_scope, line);

	int if_quadID = get_quad_count();
	new_quad(op, NULL, left, right, NO_LABEL);

	int jump_quadID = get_quad_count();
	new_quad(_jump, NULL, NULL, NULL, NO_LABEL);

	expr->PendingTrueJumps = create_pending_label(if_quadID);
	expr->PendingFalseJumps = create_pending_label(jump_quadID);

	return expr;
}

static void print_quads_reverse(Expr *expr, SymTable_T sym_table, int current_scope, int line){

        if(expr == NULL)
                return;

        print_quads_reverse(expr->next, sym_table, current_scope, line);
        new_quad(_param, NULL, emit_bool_expr(expr, sym_table, current_scope, line), NULL, NO_LABEL);
}

void handle_param_quads(ExprList *params, SymTable_T sym_table, int current_scope, int line){

	if(params == NULL)
		return;

	print_quads_reverse(params->head, sym_table, current_scope, line);
}

Expr* make_call(Expr *func, ExprList *params, SymTable_T sym_table, int current_scope, int line){

	Symbol *tmp;
	Expr *res;
	Expr *callable;

	handle_param_quads(params, sym_table, current_scope, line);

	callable = emit_table_item(func, sym_table, current_scope, line);
	new_quad(_call, NULL, emit_bool_expr(callable, sym_table, current_scope, line), NULL, NO_LABEL);

	tmp = new_tmp(sym_table, current_scope, line);
	res = lvalue_expr(tmp, var);

	new_quad(getretval, res, NULL, NULL, NO_LABEL);

	return res;
}

Expr* create_member(Expr *table, char *name, Expr *index){

	Expr *item = create_expr(tableitem);

	item->sym = table->sym;
	
	if(name != NULL) item->table_index = str_const_expr(name);
	if(index != NULL) item->table_index = index;

	return item;
}

Expr* emit_table_item(Expr *item, SymTable_T sym_table, int current_scope, int line){

	if(item->type != tableitem)
		return item;

	Symbol *tmp = new_tmp(sym_table, current_scope, line);
        Expr *res = lvalue_expr(tmp, var);
	Expr *table = lvalue_expr(item->sym, var);

	new_quad(tablegetelem, res, table, item->table_index, NO_LABEL);

	return res;
}

Expr* create_table(SymTable_T sym_table, int current_scope, int line){

	Symbol *tmp = new_tmp(sym_table, current_scope, line);
        Expr *table = lvalue_expr(tmp, newtable);

	new_quad(tablecreate, table, NULL, NULL, NO_LABEL);

	return table;
}

void add_elist_to_table(ExprList *elist, Expr *table, SymTable_T sym_table, int current_scope, int line){

	Expr *expr;
	int index = 0;

	for(expr = elist->head; expr != NULL; expr = expr->next)
		new_quad(tablesetelem, table, num_const_expr(index++), emit_bool_expr(expr, sym_table, current_scope, line), NO_LABEL);
}

void add_indexed_to_table(IndexedList *list, Expr *table, SymTable_T sym_table, int current_scope, int line){

        Indexed *ind;

        for(ind = list->head; ind != NULL; ind = ind->next)
                new_quad(tablesetelem, table, emit_bool_expr(ind->index, sym_table, current_scope, line), emit_bool_expr(ind->val, sym_table, current_scope, line), NO_LABEL);
}

Expr* handle_pre_inc_dec(Expr *lvalue, opcode op, SymTable_T sym_table, int current_scope, int line){

	assert(op == _add || op == _sub);

	Symbol *tmp = new_tmp(sym_table, current_scope, line);
	Expr *result = lvalue_expr(tmp, assignexpr);

	if(lvalue->type != tableitem){
		new_quad(op, lvalue, lvalue, num_const_expr(1), NO_LABEL);
		new_quad(_assign, result, lvalue, NULL, NO_LABEL);
	}
	else {
		Expr *table = lvalue_expr(lvalue->sym, var);
		Symbol *tmp2 = new_tmp(sym_table, current_scope, line);		

		Expr *old_value = emit_table_item(lvalue, sym_table, current_scope, line);
		Expr *new_value = lvalue_expr(tmp2, arithexpr);		

		new_quad(op, new_value, old_value, num_const_expr(1), NO_LABEL);
		new_quad(tablesetelem, table, lvalue->table_index, new_value, NO_LABEL);
		new_quad(_assign, result, new_value, NULL, NO_LABEL);
	}

	return result;
}

Expr* handle_post_inc_dec(Expr *lvalue, opcode op, SymTable_T sym_table, int current_scope, int line){

	assert(op == _add || op == _sub);

	Symbol *tmp = new_tmp(sym_table, current_scope, line);
        Expr *result = lvalue_expr(tmp, assignexpr);

	if(lvalue->type != tableitem){
		new_quad(_assign, result, lvalue, NULL, NO_LABEL);
                new_quad(op, lvalue, lvalue, num_const_expr(1), NO_LABEL);
        }
	else{
		Expr *table = lvalue_expr(lvalue->sym, var);
                Symbol *tmp2 = new_tmp(sym_table, current_scope, line);

		Expr *old_value = emit_table_item(lvalue, sym_table, current_scope, line);
                Expr *new_value = lvalue_expr(tmp2, arithexpr);

		new_quad(_assign, result, old_value, NULL, NO_LABEL);
		new_quad(op, new_value, old_value, num_const_expr(1), NO_LABEL);
		new_quad(tablesetelem, table, lvalue->table_index, new_value, NO_LABEL);
	}

	return result;
}

Expr* convert_expr_to_bool(Expr *expr, SymTable_T sym_table, int current_scope, int line){

	assert(expr != NULL);

	if(expr->PendingTrueJumps != NULL || expr->PendingFalseJumps != NULL)
		return expr;

	expr->type = boolexpr;

	int if_quadID = get_quad_count();
	new_quad(if_eq, NULL, expr, bool_const_expr(True), NO_LABEL);

	int jump_quadID = get_quad_count();
	new_quad(_jump, NULL, NULL, NULL, NO_LABEL);

	expr->PendingTrueJumps = create_pending_label(if_quadID);
	expr->PendingFalseJumps = create_pending_label(jump_quadID);

	return expr;
}
