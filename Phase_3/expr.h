#ifndef EXPR_H
#define EXPR_H

#include "symbol.h"
#include "pending_stmt_quads.h"

typedef struct Expr {
	Symbol *sym;
	char *type;
	double num_const;
	char *str_const;
	int bool_const;
	PendingQuads *TrueList;
	PendingQuads *FalseList;
	struct Expr *next;	
} Expr;

typedef struct ExprList {
	Expr *head;
	Expr *tail;
} ExprList;

#endif
