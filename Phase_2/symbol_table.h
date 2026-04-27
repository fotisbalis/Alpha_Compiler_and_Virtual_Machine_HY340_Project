

typedef struct SymTable *SymTable_T;

typedef struct Symbol {
	char* name;
	char* type;
	int scope;
	int line;
	int isActive;	
} Symbol;

/* creates and returns a symbol */
Symbol* Symbol_create(char* name, char* type, int scope, int line, int isActive);

/* creates and returns a symbol table */
SymTable_T SymTable_create(void);

/* destructor of the sym table */
void SymTable_free(SymTable_T oSymTable);

/* inserts a symbol */
void SymTable_put(SymTable_T oSymTable, Symbol* sym);

/* lookup in one scope */
Symbol* SymTable_lookup_scope(SymTable_T oSymTable, char *name, int scope);

/* lookup in all scopes with special handling of functions */
Symbol* SymTable_lookup(SymTable_T oSymTable, char *name, int current_scope, int function_depth, int* function_scopes);

/* hides a scope */
void SymTable_hide_scope(SymTable_T oSymTable, int scope);

/* prints the entire sym table per scope */
void SymTable_print(SymTable_T oSymTable);

