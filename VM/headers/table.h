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

int are_table_keys_equal(const avm_memcell *left_key, const avm_memcell *right_key);

avm_table_bucket *create_bucket(const avm_memcell *key, const avm_memcell *value);

void destroy_bucket_list(avm_table_bucket *bucket);

void delete_bucket(avm_table *table, avm_table_bucket **bucket_head, const avm_memcell *key);

#endif
