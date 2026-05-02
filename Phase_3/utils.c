#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	add_pending_label(if_quadID, get_quad_count());
	new_quad(_assign, expr, NULL, bool_const_expr(True), NO_LABEL);

	add_pending_label(jump_quadID, get_quad_count());

	return expr;
}


