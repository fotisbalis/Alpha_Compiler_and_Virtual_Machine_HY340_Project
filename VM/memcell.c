#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "memcell.h"

avm_memcell *stack = NULL;

avm_memcell *create_stack() {
	
	int i;

	if(stack == NULL) {
		stack = malloc(STACK_SIZE * sizeof(avm_memcell));
		assert(stack != NULL);
	}

	for(i = 0; i < STACK_SIZE; i++) {
		stack[i].type = undef_m;
		stack[i].data.strVal = NULL;
	}

	return stack;
}

void reset_stack() {
	
	int i;
	assert(stack != NULL);

	for(i = 0; i < STACK_SIZE; i++)
		clear_memcell(&stack[i]);
}

void free_stack() {

	int i;

	if(stack == NULL)
		return;

	reset_stack();

	free(stack);
	stack = NULL;
}

void clear_memcell(avm_memcell *memcell) {

	assert(memcell != NULL);

	if(memcell->type == string_m && memcell->data.strVal != NULL) {
		free(memcell->data.strVal);
		memcell->data.strVal = NULL;
	}
	else if(memcell->type == libfunc_m && memcell->data.libfuncVal != NULL) {
		free(memcell->data.libfuncVal);
		memcell->data.libfuncVal = NULL;
	}

	memcell->type = undef_m;
}

void copy_memcell(avm_memcell *left_memcell, avm_memcell *right_memcell) {

	assert(left_memcell != NULL);
        assert(right_memcell != NULL);

        left_memcell->type = right_memcell->type;

        switch(right_memcell->type) {
                case number_m:
                        left_memcell->data.numVal = right_memcell->data.numVal;
                        break;

		case string_m:
                        if(right_memcell->data.strVal != NULL) {
                                left_memcell->data.strVal = strdup(right_memcell->data.strVal);
                                assert(left_memcell->data.strVal != NULL);
                        }
                        else
                                left_memcell->data.strVal = NULL;
                        break;

		case bool_m:
                        left_memcell->data.boolVal = right_memcell->data.boolVal;
                        break;

		case table_m:
                        left_memcell->data.tableVal = right_memcell->data.tableVal;
                        break;

		case userfunc_m:
                        left_memcell->data.funcVal = right_memcell->data.funcVal;
                        break;

		case libfunc_m:
                        if(right_memcell->data.libfuncVal != NULL) {
                                left_memcell->data.libfuncVal = strdup(right_memcell->data.libfuncVal);
                                assert(left_memcell->data.libfuncVal != NULL);
                        }
                        else
                                left_memcell->data.libfuncVal = NULL;
                        break;

		case nil_m:
			left_memcell->data.strVal = NULL;
                        break;

		case undef_m:
                        left_memcell->data.strVal = NULL;
                        break;

		default:
                        assert(0);
        }
}

void assign_memcell(avm_memcell *left_memcell, avm_memcell *right_memcell) {

	assert(left_memcell != NULL);
	assert(right_memcell != NULL);

	if(left_memcell == right_memcell)
		return;

	if(left_memcell->type == table_m &&
	   right_memcell->type == table_m &&
	   left_memcell->data.tableVal == right_memcell->data.tableVal)
		return;

	clear_memcell(left_memcell);
	copy_memcell(left_memcell, right_memcell);
}

int memcell_to_bool(const avm_memcell *memcell) {
	
	assert(memcell != NULL);

	switch(memcell->type) {
		case number_m:
			return memcell->data.numVal != 0;
		case string_m:
			return memcell->data.strVal != NULL && memcell->data.strVal[0] != '\0';
		case bool_m:
			return memcell->data.boolVal != 0;
		case table_m:
			return True;
		case userfunc_m:
			return True;
		case libfunc_m:
			return True;
		case nil_m:
			return False;
		case undef_m:
			return False;
		default:
			assert(0);
	}
}

int are_equal(const avm_memcell *left_memcell, const avm_memcell *right_memcell) {
	
	assert(left_memcell != NULL);
	assert(right_memcell != NULL);

	if(left_memcell->type == undef_m || right_memcell->type == undef_m)
		return False;

	if(left_memcell->type == nil_m || right_memcell->type == nil_m)
		return left_memcell->type == nil_m && right_memcell->type == nil_m;

	if(left_memcell->type == bool_m || right_memcell->type == bool_m)
		return memcell_to_bool(left_memcell) == memcell_to_bool(right_memcell);

	if(left_memcell->type != right_memcell->type)
		return False;

	switch(left_memcell->type) {
		case number_m:
			return left_memcell->data.numVal == right_memcell->data.numVal;
		case string_m:
			return strcmp(left_memcell->data.strVal, right_memcell->data.strVal) == 0;
		case userfunc_m:
			return left_memcell->data.funcVal == right_memcell->data.funcVal;
		case libfunc_m:
			return strcmp(left_memcell->data.libfuncVal, right_memcell->data.libfuncVal) == 0;
		case table_m:
			return left_memcell->data.tableVal == right_memcell->data.tableVal;
		case bool_m:
			return left_memcell->data.boolVal == right_memcell->data.boolVal;
		case nil_m:
			return True;
		case undef_m:
			return False;
		default:
			assert(0);
	}
}
