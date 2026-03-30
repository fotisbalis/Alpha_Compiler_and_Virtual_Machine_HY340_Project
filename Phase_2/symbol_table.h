#include <stddef.h>
#include <assert.h>

typedef struct SymTable *SymTable_T;

typedef struct Symbol {
	char* name;
	char* type;
	int scope;
	int line;
	int isActive;	
} Symbol;

Symbol* Symbol_create(char* name, char* type, int scope, int line, int isActive);

SymTable_T SymTable_create(void);

void SymTable_free(SymTable_T oSymTable);

void SymTable_put(SymTable_T oSymTable, Symbol* sym);

Symbol* SymTable_lookup_scope(SymTable_T oSymTable, char *name, int scope);

Symbol* SymTable_lookup(SymTable_T oSymTable, char *name, int current_scope);

void SymTable_hide_scope(SymTable_T oSymTable, int scope);

void SymTable_unhide_scope(SymTable_T oSymTable, int scope);

void SymTable_print(SymTable_T oSymTable);

