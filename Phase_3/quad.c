#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "quad.h"

#define NO_LABEL -1

static int count = 0;
static int capacity = 0;
static Quad *Quads = NULL;

Quad* create_quad(opcode op, Expr *arg1, Expr *arg2, Expr *res, int label){
	
	Quad *quad = malloc(sizeof(Quad));

	quad->op = op;
	quad->arg1 = arg1;
	quad->arg2 = arg2;
	quad->res = res;
	quad->label = label;

	return quad;
}

void add_new_quad(Quad quad){

	if(count >= capacity) expand_quads();

	quad.id = count;
	Quads[count] = quad;
	
	count++;
}

void expand_quads(){
	
	Quad *tmpQquads;
	
	capacity += 100;

	tmpQuads = realloc(Quads, capacity * sizeof(Quad));

	Quads = tmpQuads;
}

Quad* get_quads(){
	
	return Quads;
}

int quad_count(){

	return count;
}

void add_pending_label(int quadID, int label){

	assert(quadID >= 0 && quadID < count);
	assert(Quads[quadID].label == NO_LABEL);

	Quads[quadID].label = label;
}

char* opcode_to_string(opcode op){
    switch(op){
        case _assign:      return "assign";
        case _add:         return "add";
        case _sub:         return "sub";
        case _mul:         return "mul";
        case _div:         return "div";
        case _mod:         return "mod";
        case _uminus:      return "uminus";
        case _and:         return "and";
        case _or:          return "or";
        case _not:         return "not";
        case if_eq:        return "if_eq";
        case if_noteq:     return "if_noteq";
        case if_lesseq:    return "if_lesseq";
        case if_greatereq: return "if_greatereq";
        case if_less:      return "if_less";
        case if_greater:   return "if_greater";
        case _jump:        return "jump";
        case _call:        return "call";
        case _param:       return "param";
        case _return:      return "return";
        case getretval:    return "getretval";
        case funcstart:    return "funcstart";
        case funcend:      return "funcend";
	case tablecreate:  return "tablecreate";
	case tablegetelem: return "tablegetelem";
        case tablesetelem: return "tablesetelem";
        default:
			   return NULL;
    }
}

void print_quads(FILE *f){
	
	int i;

	assert(f != NULL);

	fprintf(f, "quad#  opcode  result  arg1   arg2   label\n");
	fprintf(f, "-----------------------------------------------\n");

	for(i = 0; i < count; i++){
		
		fprintf(f, "%d:  %s %s %s %s",
			quads[i].id,
			opcode_to_string(Quads[i].op),
			expr_to_string(Quads[i].res),
			expr_to_string(Quads[i].arg1),
			expr_to_string(Quads[i].arg2)
		);

        	if(quads[i].label != NO_LABEL)
			fprintf(f, "%d", Quads[i].label);

		fprintf(f, "\n");
	}

	fprintf(f, "\n-----------------------------------------------\n");
}

void free_quads(){

	free(Quads);
	Quads = NULL;
	count = 0;
	capacity = 0;
}



