#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void print_reduce(char *left, char* right){
        printf("%s -> %s\n", left, right);
}

Symbol* check_for_lib_func(SymTable_T oSymTable, char *name){
	
	Symbol* lib = SymTable_lookup_scope(oSymTable, name, 0);

        if(lib != NULL && strcmp(lib->type, "library function") == 0)
        	return lib;

	return NULL;
}
