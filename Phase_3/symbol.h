#ifndef SYMBOL_H
#define SYMBOL_H

typedef struct Symbol {
        char* name;
        char* type;
        int scope;
        int line;
        int isActive;
} Symbol;

Symbol* Symbol_create(char* name, char* type, int scope, int line, int isActive);

#endif
