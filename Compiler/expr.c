#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "headers/expr.h"

Expr* create_expr(expr_type type){

	Expr *expr = malloc(sizeof(Expr));

	expr->sym = NULL;
	expr->type = type;
	expr->num_const = 0;
	expr->str_const = NULL;
	expr->bool_const = 0;
	expr->PendingTrueJumps = NULL;
	expr->PendingFalseJumps = NULL;
	expr->next = NULL;
	
	return expr;
}

Expr* lvalue_expr(Symbol *sym, expr_type type){
	
	assert(sym != NULL);

	Expr *expr = create_expr(type);
	expr->sym = sym;

	return expr;
}

Expr* num_const_expr(double num){

	Expr *expr = create_expr(constnum);
	expr->num_const = num;

	return expr;
}

Expr* str_const_expr(char *str){

	Expr *expr = create_expr(conststring);
        expr->str_const = strdup(str);

	return expr;
}

Expr* bool_const_expr(int boolean){

	assert(boolean == 0 || boolean == 1);

	Expr *expr = create_expr(constbool);
        expr->bool_const = boolean;

        return expr;
}

Expr* nil_expr(){

	Expr *expr = create_expr(nil);

        return expr;
}

Expr* error_expr(expr_type type){

	return create_expr(type);
}

ExprList* create_expr_list(){
	
	ExprList *list = malloc(sizeof(ExprList));

	list->head = NULL;
    	list->tail = NULL;

	return list;
}

void add_expr(ExprList *list, Expr *expr){

	assert(list != NULL && expr != NULL && expr->next == NULL);

	if(list->head == NULL){
		list->head = expr;
		list->tail = expr;
	}
	else{
		list->tail->next = expr;
		list->tail = expr;
	}
}

char* expr_to_string(Expr *expr){

	char tmp[64];

	if(expr == NULL)
		return "";

	if(expr->sym != NULL)
        	return strdup(expr->sym->name);

	switch(expr->type){
		
		case var:
			return strdup("var");

		case tableitem:
			return strdup("tableitem");

        	case programfunc:
			return strdup("programfunc");

        	case libraryfunc:
			return strdup("libraryfunc");

        	case arithexpr:
			return strdup("arithexpr");

        	case boolexpr:
			return strdup("boolexpr");

        	case assignexpr:
			return strdup("assignexpr");
        
		case newtable:
			return strdup("newtable");
        
		case constnum:
			sprintf(tmp, "%g", expr->num_const);
            		return strdup(tmp);

        	case constbool:
			sprintf(tmp, expr->bool_const == 0 ? "false" : "true");
			return strdup(tmp);

        	case conststring:
			if(expr->str_const == NULL) return NULL;
			sprintf(tmp, "\"%s\"", expr->str_const);
			return strdup(tmp);

        	case nil:
			return strdup("nil");

		default:
			return "";	
	}
}

void swap_true_false_lists(Expr *expr){

        PendingLabel *tmp;

        assert(expr != NULL);

	tmp = expr->PendingTrueJumps;
	expr->PendingTrueJumps = expr->PendingFalseJumps;
	expr->PendingFalseJumps = tmp;
}
