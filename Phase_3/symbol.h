#ifndef SYMBOL_H
#define SYMBOL_H

typedef enum scopespace {
	programvar,
	functionlocal,
	formalarg
} scopespace;

typedef struct Symbol {
        char* name;
        char* type;
        int scope;
        int line;
        int isActive;
	int isTemp;
	int offset;
	scopespace space;
} Symbol;

Symbol* Symbol_create(char* name, char* type, int scope, int line, int isActive, int isTemp);

scopespace current_scope_space();

int current_scope_offset();

void inc_current_scope_offset();

void enter_scope_space();

void exit_scope_space();

#endif
