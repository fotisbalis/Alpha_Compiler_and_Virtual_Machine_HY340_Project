#ifndef EXPR_H
#define EXPR_H

#include "symbol.h"
#include "pending_labels.h"

typedef enum expr_type {
	var,
	tableitem,
	programfunc,
	libraryfunc,
	arithexpr,
	boolexpr,
	assignexpr,
	newtable,
	constnum,
	constbool,
	conststring,
	nil
} expr_type;

typedef struct Expr {
	Symbol *sym;
	expr_type type;
	struct Expr *table_index;
	double num_const;
	char *str_const;
	int bool_const;
	PendingLabel *PendingTrueJumps;
	PendingLabel *PendingFalseJumps;
	struct Expr *next;	
} Expr;

typedef struct ExprList {
	Expr *head;
	Expr *tail;
} ExprList;

Expr* create_expr(expr_type type);

Expr* lvalue_expr(Symbol *sym, expr_type type);

Expr* num_const_expr(double num);

Expr* str_const_expr(char *str);

Expr* bool_const_expr(int boolean);

Expr* nil_expr();

ExprList* create_expr_list();

void add_expr(ExprList *list, Expr *expr);

char* expr_to_string(Expr *expr);

void swap_true_false_lists(Expr *expr);

#endif
