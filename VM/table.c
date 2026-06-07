#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "headers/table.h"

static int hash_string_key(const char *key);
static int hash_number_key(double key);

static int get_bucket_index(const avm_memcell *key);

avm_table *create_table() {

	avm_table *table;
	int i;

	table = malloc(sizeof(avm_table));
	assert(table != NULL);

	table->refCounter = 0;
	table->total = 0;

	for(i = 0; i < AVM_TABLE_HASHSIZE; i++) {
		table->stringIndexed[i] = NULL;
		table->numberIndexed[i] = NULL;
	}

	return table;
}

void destroy_table(avm_table *table) {

	assert(table != NULL);

	int i;
	for(i = 0; i < AVM_TABLE_HASHSIZE; i++) {
		destroy_bucket_list(table->stringIndexed[i]);
		destroy_bucket_list(table->numberIndexed[i]);
	}

	free(table);
}

void destroy_bucket_list(avm_table_bucket *bucket) {

        avm_table_bucket *current_bucket;
        avm_table_bucket *next_bucket;

        current_bucket = bucket;

        while(current_bucket != NULL) {
                next_bucket = current_bucket->next;
                clear_memcell(&current_bucket->key);
                clear_memcell(&current_bucket->value);
                free(current_bucket);
                current_bucket = next_bucket;
        }
}

void inc_table_refcounter(avm_table *table) {
	assert(table != NULL);
	assert(table->refCounter >= 0);

	table->refCounter++;
}

void dec_table_refcounter(avm_table *table) {
	assert(table != NULL);
	assert(table->refCounter > 0);

	table->refCounter--;

	if(table->refCounter == 0)
		destroy_table(table);
}

avm_memcell *get_table_element(avm_table *table, avm_memcell *key) {
	
	avm_table_bucket **bucket_array;
	avm_table_bucket *bucket;
	int bucket_index;

	assert(table != NULL);
	assert(key != NULL);

	if(key->type == string_m)
                bucket_array = table->stringIndexed;
	else if(key->type == number_m)
                bucket_array = table->numberIndexed;
        else
                return NULL;

	bucket_index = get_bucket_index(key);
	assert(bucket_index >= 0);
	assert(bucket_index < AVM_TABLE_HASHSIZE);

	for(bucket = bucket_array[bucket_index]; bucket != NULL; bucket = bucket->next) {
                if(are_table_keys_equal(&bucket->key, key))
                        break;
        }

	if(bucket == NULL)
		return NULL;

	return &bucket->value;
}

void set_table_element(avm_table *table, avm_memcell *key, avm_memcell *value) {
	
	avm_table_bucket **bucket_array;
	avm_table_bucket *bucket;
	avm_table_bucket *new_bucket;
	int bucket_index;

	assert(table != NULL);
	assert(key != NULL);
	assert(value != NULL);

	if(key->type == string_m)
                bucket_array = table->stringIndexed;
	else if(key->type == number_m)
                bucket_array = table->numberIndexed;
	else
		return;

	bucket_index = get_bucket_index(key);
	assert(bucket_index >= 0);
	assert(bucket_index < AVM_TABLE_HASHSIZE);

	if(value->type == nil_m) {
		delete_bucket(table, &bucket_array[bucket_index], key);
		return;
	}

	for(bucket = bucket_array[bucket_index]; bucket != NULL; bucket = bucket->next) {
                if(are_table_keys_equal(&bucket->key, key))
                        break;
        }

	if(bucket != NULL) {
		assign_memcell(&bucket->value, value);
		return;
	}

	new_bucket = create_bucket(key, value);
	new_bucket->next = bucket_array[bucket_index];
	bucket_array[bucket_index] = new_bucket;
	table->total++;
}

static int hash_string_key(const char *key) {
	
	unsigned long hash;
	int i;

	assert(key != NULL);

	hash = 0;

	for(i = 0; key[i] != '\0'; i++)
		hash = hash * 65599 + (unsigned char) key[i];

	return (int) (hash % AVM_TABLE_HASHSIZE);
}

static int hash_number_key(double key) {
	unsigned char *bytes;
	unsigned long hash;
	int i;

	bytes = (unsigned char *) &key;
	hash = 0;

	for(i = 0; i < (int) sizeof(double); i++)
		hash = hash * 65599 + bytes[i];

	return (int) (hash % AVM_TABLE_HASHSIZE);
}

static int get_bucket_index(const avm_memcell *key) {
	
	assert(key != NULL);

	if(key->type == string_m) {
		assert(key->data.strVal != NULL);
		return hash_string_key(key->data.strVal);
	}

	if(key->type == number_m)
		return hash_number_key(key->data.numVal);

	assert(0);
	return -1;
}

int are_table_keys_equal(const avm_memcell *left_key, const avm_memcell *right_key) {
	
	assert(left_key != NULL);
	assert(right_key != NULL);

	if(left_key->type == string_m && right_key->type == string_m) {
		assert(left_key->data.strVal != NULL);
		assert(right_key->data.strVal != NULL);
		
		if(strcmp(left_key->data.strVal, right_key->data.strVal) == 0)
			return True;
	}

	if(left_key->type == number_m && right_key->type == number_m)
		if(left_key->data.numVal == right_key->data.numVal)
			return True;

	return False;
}

avm_table_bucket *create_bucket(const avm_memcell *key, const avm_memcell *value) {
	
	avm_table_bucket *bucket;

	assert(key != NULL);
	assert(value != NULL);

	bucket = malloc(sizeof(avm_table_bucket));
	assert(bucket != NULL);

	bucket->key.type = undef_m;
	bucket->key.data.strVal = NULL;
	bucket->value.type = undef_m;
	bucket->value.data.strVal = NULL;
	bucket->next = NULL;

	assign_memcell(&bucket->key, (avm_memcell *) key);
	assign_memcell(&bucket->value, (avm_memcell *) value);

	return bucket;
}

void delete_bucket(avm_table *table, avm_table_bucket **bucket_head, const avm_memcell *key) {
	
	avm_table_bucket *current_bucket;
	avm_table_bucket *previous_bucket;

	assert(table != NULL);
	assert(bucket_head != NULL);
	assert(key != NULL);

	current_bucket = *bucket_head;
	previous_bucket = NULL;

	while(current_bucket != NULL) {
		if(are_table_keys_equal(&current_bucket->key, key)) {
			if(previous_bucket == NULL)
				*bucket_head = current_bucket->next;
			else
				previous_bucket->next = current_bucket->next;

			clear_memcell(&current_bucket->key);
			clear_memcell(&current_bucket->value);
			free(current_bucket);
			table->total--;
			return;
		}

		previous_bucket = current_bucket;
		current_bucket = current_bucket->next;
	}
}
