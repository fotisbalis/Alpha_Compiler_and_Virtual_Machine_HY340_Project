#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "headers/symbol.h"

#define True 1
#define False 0

static int offset = 0;
static int program_var_offset = 0;
static int function_local_offset = 0;
static int formal_arg_offset = 0;
static int scope_space_counter = 1;

scopespace current_scope_space(){

	if(scope_space_counter == 1) 
		return programvar;
	
	else if(scope_space_counter % 2 == 0) 
		return formalarg;

	else 
		return functionlocal;
}

int current_scope_offset(){
	
	switch(current_scope_space()) {

		case programvar: return program_var_offset;

		case formalarg: return formal_arg_offset;

		case functionlocal: return function_local_offset;

		default: assert(False);
	}
}

void inc_current_scope_offset(){

	switch(current_scope_space()) {

                case programvar:
			program_var_offset++;
			return;

                case formalarg: 
			formal_arg_offset++;
			return;

                case functionlocal: 
			function_local_offset++;
			return;

                default: assert(False);
        }

}

void enter_scope_space(){

	scope_space_counter++;
}

void exit_scope_space(){

	scope_space_counter--;
}

void reset_formal_arg_offset(){

	formal_arg_offset = 0;
}

void reset_function_local_offset(){

	function_local_offset = 0;
}

Symbol* Symbol_create(char* name, char* type, int scope, int line, int isActive, int isTemp){
        
	Symbol* sym = malloc(sizeof(Symbol));

	sym->name = strdup(name);
        sym->type = strdup(type);

        assert(scope >= 0 && line >= 0);
        sym->scope = scope;
        sym->line = line;

        assert(isActive == True || isActive == False);
        sym->isActive = isActive;

	assert(isTemp == True || isTemp == False);
        sym->isTemp = isTemp;

	sym->space = current_scope_space();
	sym->offset = current_scope_offset();
	sym->taddress = -1;
	sym->localSize = 0;

	inc_current_scope_offset();

        return sym;
}
