#ifndef EXPR_H
#define EXPR_H

#include "symbol.h"
#include "pending_labels.h"

typedef struct Expr {
	Symbol *sym;
	char *type;
	double num_const;
	char *str_const;
	int bool_const;
	PendingLabel *TrueList;
	PendingLabel *FalseList;
	struct Expr *next;	
} Expr;

typedef struct ExprList {
	Expr *head;
	Expr *tail;
} ExprList;

#endif
