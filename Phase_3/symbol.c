#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "symbol.h"

Symbol* Symbol_create(char* name, char* type, int scope, int line, int isActive, int isTemp){
        
	Symbol* sym = malloc(sizeof(Symbol));
        
	sym->name = strdup(name);
        sym->type = strdup(type);

        assert(scope >= 0 && line >= 0);
        sym->scope = scope;
        sym->line = line;

        assert(isActive == 0 || isActive == 1);
        sym->isActive = isActive;

	assert(isTemp == 0 || isTemp == 1);
        sym->isTemp = isTemp;

        return sym;
}
