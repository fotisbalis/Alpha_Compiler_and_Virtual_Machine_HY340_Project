#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "avm_utils.h"

static avm_memcell *translate_global_operand(const avm_operand *operand);
static avm_memcell *translate_local_operand(const avm_operand *operand);
static avm_memcell *translate_formal_operand(const avm_operand *operand);

void runtime_error(const char *message) {
	assert(message != NULL);

	fprintf(stderr, "Runtime Error: %s\n", message);
	set_execution_finished(True);
}

avm_memcell *translate_operand(const avm_operand *operand, avm_memcell *reg) {
	avm_binary *binary;

	assert(operand != NULL);

	binary = get_program_binary();
	assert(binary != NULL);

	switch(operand->type) {
		case global_a:
			return translate_global_operand(operand);

		case local_a:
			return translate_local_operand(operand);

		case formal_a:
			return translate_formal_operand(operand);

		case retval_a:
			return get_retval_register();

		case number_a:
			assert(reg != NULL);
			assert((int) operand->val >= 0);
			assert((int) operand->val < binary->number_count);
			
			reset_register(reg);
			reg->type = number_m;
			reg->data.numVal = binary->number_consts[operand->val];
			return reg;

		case string_a:
			assert(reg != NULL);
			assert((int) operand->val >= 0);
			assert((int) operand->val < binary->string_count);
			
			reset_register(reg);
			reg->type = string_m;
			reg->data.strVal = strdup(binary->string_consts[operand->val]);
			assert(reg->data.strVal != NULL);
			return reg;

		case bool_a:
			assert(reg != NULL);
			assert(operand->val == 0 || operand->val == 1);
			
			reset_register(reg);
			reg->type = bool_m;
			reg->data.boolVal = (int) operand->val;
			return reg;

		case nil_a:
			assert(reg != NULL);
			
			reset_register(reg);
			reg->type = nil_m;
			return reg;

		case userfunc_a:
			assert(reg != NULL);
			assert((int) operand->val >= 0);
			assert((int) operand->val < binary->userfunc_count);
			
			reset_register(reg);
			reg->type = userfunc_m;
			reg->data.funcVal = binary->userfuncs[operand->val].address;
			return reg;

		case libfunc_a:
			assert(reg != NULL);
			assert((int) operand->val >= 0);
			assert((int) operand->val < binary->libfunc_count);
			
			reset_register(reg);
			reg->type = libfunc_m;
			reg->data.libfuncVal = strdup(binary->libfuncs[operand->val]);
			assert(reg->data.libfuncVal != NULL);
			return reg;

		case label_a:
			return NULL;

		case unused_a:
			return NULL;

		default:
			assert(0);
			return NULL;
	}
}

static avm_memcell *translate_global_operand(const avm_operand *operand) {
	
	int stack_index;

	assert(operand != NULL);
	assert(operand->type == global_a);
	assert(stack != NULL);
	assert((int) operand->val >= 0);
	assert((int) operand->val < get_global_count());

	stack_index = (STACK_SIZE - 1) - (int) operand->val;

	assert(stack_index >= 0);
	assert(stack_index < STACK_SIZE);

	return &stack[stack_index];
}

static avm_memcell *translate_local_operand(const avm_operand *operand) {
	
	int stack_index;

	assert(operand != NULL);
	assert(operand->type == local_a);
	assert(stack != NULL);
	assert((int) operand->val >= 0);

	stack_index = get_topsp() - (int) operand->val;

	assert(stack_index >= 0);
	assert(stack_index < STACK_SIZE);

	return &stack[stack_index];
}

static avm_memcell *translate_formal_operand(const avm_operand *operand) {
	
	int stack_index;

	assert(operand != NULL);
	assert(operand->type == formal_a);
	assert(stack != NULL);
	assert((int) operand->val >= 0);

	stack_index = get_topsp() + STACKENV_SIZE + 1 + (int) operand->val;

	assert(stack_index >= 0);
	assert(stack_index < STACK_SIZE);

	return &stack[stack_index];
}
