#ifndef MEMCELL_H
#define MEMCELL_H

#include "avm_types.h"

#define STACK_SIZE 4096

typedef struct avm_table avm_table;

typedef struct avm_memcell {
	int type;
	union {
		double numVal;
		char *strVal;
		int boolVal;
		avm_table *tableVal;
		int funcVal;
		char *libfuncVal;
	} data;
} avm_memcell;

avm_memcell *create_stack();

void reset_stack();

void free_stack();

void clear_memcell(avm_memcell *memcell);

void copy_memcell(avm_memcell *left_memcell, avm_memcell *right_memcell);

void assign_memcell(avm_memcell *left_memcell, avm_memcell *right_memcell);

#endif
