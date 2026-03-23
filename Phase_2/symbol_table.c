#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sym_table.h"

#define HASH_SIZE 509
#define MAX_SCOPE 100

ypedef struct node {
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
		hash = hash * HASH_SIZE + key[i];
	}

	return hash % HASH_SIZE;
}

/* Create table */
SymTable_T SymTable_new(void){
	SymTable_T newSymTable = (struct ymTable)malloc(sizeof(struct SymTable));

	/* Allocate the memory for 509 buckets initially */
	newSymTable->buckets = (node**)malloc(509*sizeof(node*));
	newSymTable->size = 509;

	/* Initialize buckets to NULL */
	for(int i = 0; i < newSymTable->size; i++) {
		newSymTable->buckets[i] = NULL;
	}

	return newSymTable;
}

/* Insert */
void SymTable_put(SymTable_T oSymTable, Symbol* sym) {
	node *n, *new;
	int index;
	char name_scope[1000];
	
	sprintf(name_scope, "%s%d", sym->name, sym->scope);

	index = SymTable_hash(name_scope);

	assert(oSymTable != NULL && name != NULL);

	/* Check if the key already exists in the bucket and return 0 if it does */
	for(n = oSymTable->buckets[index]; n != NULL; n = n->next){
		if(strcmp(name_scope, n->key) == 0 && n->value->isActive) return;
	}

	/* Add new the new element at the start of the bucket */
	new = (node*)malloc(sizeof(node));
	new->key = strdup(scoped_name);
	new->value = sym;
	new->next = oSymTable->buckets[index];
	oSymTable->buckets[index] = new;
}

Symbol* SymTable_lookup(SymTable_T oSymTable, char *name){
	char name_scope[1000];
	int i, index;
	node *n;

	for(i = MAX_SCOPE; i >= 0; i--){ 
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

void SymTable_print(SymTable_T oSymTable){
	printf("\n--- SYMBOL TABLE ---\n");

    	for (int i = 0; i < HASH_SIZE; i++) {
        	for(n = oSymTable->buckets[index]; n != NULL; n = n->next) {
            		Symbol *s = n->value;

            		printf("Name: %s | Type: %s | Scope: %d | Line: %d | Active: %d\n", s->name, s->type, s->scope, s->line, s->isActive);
        	}
	}
    }
}
