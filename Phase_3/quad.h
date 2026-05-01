#ifndef QUAD_H
#define QUAD_H

#include <stdio.h>
#include "expr.h"

typedef enum opcode {
    	_assign,
    	_add,
    	_sub,
    	_mul,
    	_div,
    	_mod,
    	_uminus,
    	_and,
    	_or,
    	_not,
    	if_eq,
    	if_noteq,
    	if_lesseq,
    	if_greatereq,
    	if_less,
    	if_greater,
    	_jump,
    	_call,
    	_param,
    	_return,
    	getretval,
    	funcstart,
    	funcend,
    	tablecreate,
    	tablegetelem,
	tablesetelem
} opcode;

typedef struct Quad{
	int id;
	opcode op;
	Expr *arg1;
	Expr *arg2;
	Expr *res;
	int label;
} Quad;

Quad* create_quad(opcode op, Expr *arg1, Expr *arg2, Expr *res, int label);

void add_new_quad(Quad quad);

void expand_quads();

Quad* get_quads();

int quad_count();

void add_pending_label(int quadID, int label);

char* opcode_to_string(opcode op);

void print_quads(FILE *f);

void free_quads();

#endif
