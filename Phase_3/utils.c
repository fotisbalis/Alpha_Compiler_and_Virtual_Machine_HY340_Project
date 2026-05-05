#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"

#define NO_LABEL -1
#define True 1
#define False 0

static int tmp_counter = 0;

void print_reduce(char *left, char* right){
        printf("%s -> %s\n", left, right);
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

Expr* handle_comparison_quad(opcode op, Expr *arg1, Expr *arg2, SymTable_T sym_table, int current_scope, int line){

	Symbol *tmp = new_tmp(sym_table, current_scope, line);
	Expr *expr = lvalue_expr(tmp, boolexpr);

	int if_quadID = get_quad_count();
	new_quad(op, NULL, arg1, arg2, NO_LABEL);
	
	new_quad(_assign, expr, NULL, bool_const_expr(False), NO_LABEL);

	int jump_quadID = get_quad_count();
	new_quad(_jump, NULL, NULL, NULL, NO_LABEL);

	fill_pending_label(if_quadID, get_quad_count());
	new_quad(_assign, expr, NULL, bool_const_expr(True), NO_LABEL);

	fill_pending_label(jump_quadID, get_quad_count());

	return expr;
}

void print_quads_reverse(Expr *expr){

        if(expr == NULL)
                return;

        print_quads_reverse(expr->next);
        new_quad(_param, NULL, expr, NULL, NO_LABEL);
}

void handle_param_quads(ExprList *params){

	if(params == NULL)
		return;

	print_quads_reverse(params->head);
}

Expr* make_call(Expr *func, ExprList *params, SymTable_T sym_table, int current_scope, int line){

	Symbol *tmp;
	Expr *res;

	handle_param_quads(params);

	new_quad(_call, NULL, func, NULL, NO_LABEL);

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

Expr* get_table(Expr *item, SymTable_T sym_table, int current_scope, int line){

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

void add_elist_to_table(ExprList *elist, Expr *table){

	Expr *expr;
	int index = 0;

	for(expr = elist->head; expr != NULL; expr = expr->next)
		new_quad(tablesetelem, table, num_const_expr(index++), expr, NO_LABEL);
}

void add_indexed_to_table(IndexedList *list, Expr *table){

        Indexed *ind;

        for(ind = list->head; ind != NULL; ind = ind->next)
                new_quad(tablesetelem, table, ind->index, ind->val, NO_LABEL);
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

		Expr *old_value = get_table(lvalue, sym_table, current_scope, line);
		Expr *new_value = lvalue_expr(tmp2, arithexpr);		

		new_quad(op, new_value, old_value, num_const_expr(1), NO_LABEL);
		new_quad(tablesetelem, table, lvalue->table_index, new_value, NO_LABEL);
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

		Expr *old_value = get_table(lvalue, sym_table, current_scope, line);
                Expr *new_value = lvalue_expr(tmp2, arithexpr);

		new_quad(_assign, result, old_value, NULL, NO_LABEL);
		new_quad(op, new_value, old_value, num_const_expr(1), NO_LABEL);
		new_quad(tablesetelem, table, lvalue->table_index, new_value, NO_LABEL);
	}

	return result;
}

