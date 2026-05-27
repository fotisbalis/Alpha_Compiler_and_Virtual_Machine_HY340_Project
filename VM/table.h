#ifndef TABLE_H
#define TABLE_H

#include "memcell.h"

#define AVM_TABLE_HASHSIZE 211

typedef struct avm_table_bucket {
	avm_memcell key;
	avm_memcell value;
	struct avm_table_bucket *next;
} avm_table_bucket;

typedef struct avm_table {
	int refCounter;
	int total;
	avm_table_bucket *stringIndexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket *numberIndexed[AVM_TABLE_HASHSIZE];
} avm_table;

avm_table *create_table();

void destroy_table(avm_table *table);

void inc_table_refcounter(avm_table *table);

void dec_table_refcounter(avm_table *table);

avm_memcell *get_table_element(avm_table *table, avm_memcell *key);

void set_table_element(avm_table *table, avm_memcell *key, avm_memcell *value);

#endif
