#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

#define HASH_SIZE 509

int max_scope = 0;

typedef struct node {
	char *key;
	Symbol *value;
	struct node *next;
} node;

struct SymTable{
	node **buckets;
	int size; /* Number of buckets */
};

int SymTable_hash(char *key) {
	int i, hash = 0;

	for(i = 0; key[i] != '\0'; i++) {
		hash = hash * 65599 + key[i];
	}

	return hash % HASH_SIZE;
}

Symbol* Symbol_create(char* name, char* type, int scope, int line, int isActive){
	Symbol* sym = malloc(sizeof(Symbol));
    	sym->name = strdup(name);
    	sym->type = strdup(type);
	
	assert(scope >= 0 && line >= 0);
	sym->scope = scope;
    	sym->line = line;

	assert(isActive == 0 || isActive == 1);
    	sym->isActive = isActive;
    
	return sym;
}

/* Create table */
SymTable_T SymTable_create(void){
	SymTable_T newSymTable = malloc(sizeof(*newSymTable));

	/* Allocate the memory for 509 buckets initially */
	newSymTable->buckets = (node**)malloc(509*sizeof(node*));
	newSymTable->size = 509;

	/* Initialize buckets to NULL */
	for(int i = 0; i < newSymTable->size; i++) {
		newSymTable->buckets[i] = NULL;
	}

	return newSymTable;
}

/* Free table */
void SymTable_free(SymTable_T oSymTable){
	node *n, *tmp;
	int i;

    	for(i = 0; i < HASH_SIZE; i++){
        	n = oSymTable->buckets[i];
       	 	while(n){
            		tmp = n;
            		n = n->next;

            		free(tmp->key);
            		free(tmp->value->name);
            		free(tmp->value->type);
            		free(tmp->value);
            		free(tmp);
        	}
    	}

	free(oSymTable->buckets);
    	free(oSymTable);
}

/* Insert */
void SymTable_put(SymTable_T oSymTable, Symbol* sym) {
	node *n, *new;
	int index;
	char name_scope[1000];
	Symbol *s;
	
	if(sym->scope > max_scope) max_scope = sym->scope;

	sprintf(name_scope, "%s%d", sym->name, sym->scope);

	index = SymTable_hash(name_scope);

	assert(oSymTable != NULL && name_scope != NULL);

	/* Check if the key already exists in the bucket and return 0 if it does */
	for(n = oSymTable->buckets[index]; n != NULL; n = n->next){
		if(strcmp(name_scope, n->key) == 0 && n->value->isActive) return;
	}

	s = malloc(sizeof(Symbol));
	s->name = strdup(sym->name);
    	s->type = strdup(sym->type);
    	s->scope = sym->scope;
    	s->line = sym->line;
    	s->isActive = sym->isActive;
	
	/* Add new the new symbol at the start of the bucket */
	new = (node*)malloc(sizeof(node));
	new->key = strdup(name_scope);
	new->value = s;

	new->next = oSymTable->buckets[index];
	oSymTable->buckets[index] = new;
}

Symbol* SymTable_lookup(SymTable_T oSymTable, char *name, int current_scope){
	char name_scope[1000];
	int i, index;
	node *n;

	for(i = current_scope; i >= 0; i--){ 
        	sprintf(name_scope, "%s%d", name, i);

		index = SymTable_hash(name_scope);
		
		for(n = oSymTable->buckets[index]; n != NULL; n = n->next){
			if(strcmp(name_scope, n->key) == 0 && n->value->isActive) 
				return n->value;
		}
	}

	return NULL;
}

Symbol* SymTable_lookup_scope(SymTable_T oSymTable, char *name, int scope){
	char name_scope[1000];
        int index;
        node *n;

	sprintf(name_scope, "%s%d", name, scope);

 	index = SymTable_hash(name_scope);
	
	for(n = oSymTable->buckets[index]; n != NULL; n = n->next){
		if(strcmp(name_scope, n->key) == 0 && n->value->isActive) 
			return n->value;
	}

	return NULL;
}

void SymTable_hide_scope(SymTable_T oSymTable, int scope){
	node *n;
	int i;

	for(i = 0; i < HASH_SIZE; i++){

		for(n = oSymTable->buckets[i]; n != NULL; n = n->next){
			if(n->value->scope == scope)
				n->value->isActive = 0;
		}
	}
}

void SymTable_unhide_scope(SymTable_T oSymTable, int scope){
        node *n;
        int i;

        for(i = 0; i < HASH_SIZE; i++){

                for(n = oSymTable->buckets[i]; n != NULL; n = n->next){
                        if(n->value->scope == scope)
                                n->value->isActive = 1;
                }
        }
}

void SymTable_print(SymTable_T oSymTable){
	node *n;
	int i, j;

	for(i = 0; i <= max_scope; i++) {
	printf("\n--------- scope #%d ---------\n", i);
		
    		for(j = 0; j < HASH_SIZE; j++) {
        		for(n = oSymTable->buckets[j]; n != NULL; n = n->next) {
            			Symbol *s = n->value;
				
				if(s->scope == i){
            				printf("\"%s\" [%s]  (line %d) (scope %d)\n", s->name, s->type, s->line, s->scope);
				}
			}
		}
	}
}
