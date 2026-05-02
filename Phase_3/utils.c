#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

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
