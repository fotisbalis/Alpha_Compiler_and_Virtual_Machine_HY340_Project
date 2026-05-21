#ifndef INDEXED_H
#define INDEXED_H

#include "expr.h"

typedef struct Indexed {
        Expr *index;
	Expr *val;
        struct Indexed *next;
} Indexed;

typedef struct IndexedList {
        Indexed *head;
        Indexed *tail;
} IndexedList;

Indexed* create_indexed(Expr *index, Expr *val);

IndexedList* create_indexed_list();

void add_indexed(IndexedList *list, Indexed *ind);

#endif
