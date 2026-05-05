#ifndef SYMBOL_H
#define SYMBOL_H

typedef struct Symbol {
	int id;
        char* name;
        char* type;
        int scope;
        int line;
        int isActive;
	int isTemp;
} Symbol;

Symbol* Symbol_create(char* name, char* type, int scope, int line, int isActive, int isTemp);

#endif
