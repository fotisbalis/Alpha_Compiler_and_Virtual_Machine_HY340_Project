#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/avm_utils.h"

static avm_memcell *translate_global_operand(const avm_operand *operand);
static avm_memcell *translate_local_operand(const avm_operand *operand);
static avm_memcell *translate_formal_operand(const avm_operand *operand);

void runtime_error(const char *message) {
	assert(message != NULL);

	fprintf(stderr, "RUNTIME ERROR: %s\n", message);
	
	set_execution_finished(True);
}

void runtime_warning(const char *message) {
	assert(message != NULL);

	fprintf(stderr, "RUNTIME WARNING: %s\n", message);
}

int get_current_total_actuals() {
	return get_env_value(get_topsp(), NUMACTUALS_OFFSET);
}

avm_memcell *get_actual(int index) {
	int total_actuals;
	int stack_index;

	total_actuals = get_current_total_actuals();
	assert(index >= 0);
	assert(index < total_actuals);

	stack_index = get_topsp() + STACKENV_SIZE + 1 + index;
	assert(stack_index >= 0);
	assert(stack_index < STACK_SIZE);

	return &stack[stack_index];
}

int get_caller_topsp() {
	return get_env_value(get_topsp(), SAVEDTOPSP_OFFSET);
}

void set_retval_nil() {
	avm_memcell *retval;

	retval = get_retval_register();
	reset_register(retval);
	retval->type = nil_m;
}

void restore_after_libfunc_call() {

	int old_top;
	int old_topsp;
	int saved_top;
	int saved_topsp;
	int saved_pc;
	int saved_actuals;
	int i;
	int upper_bound;

	old_top = get_top();
	old_topsp = get_topsp();

	saved_topsp = get_env_value(old_topsp, SAVEDTOPSP_OFFSET);
	saved_top = get_env_value(old_topsp, SAVEDTOP_OFFSET);
	saved_pc = get_env_value(old_topsp, SAVEDPC_OFFSET);
	saved_actuals = get_env_value(old_topsp, NUMACTUALS_OFFSET);

	upper_bound = old_topsp + STACKENV_SIZE + saved_actuals;
	assert(upper_bound >= 0);
	assert(upper_bound < STACK_SIZE);

	for(i = old_top + 1; i <= upper_bound; i++)
		clear_memcell(&stack[i]);

	set_top(saved_top);
	set_topsp(saved_topsp);
	reset_total_actuals();
	set_pc(saved_pc);
}

void set_retval_table(avm_table *table) {
	avm_memcell *retval;

	assert(table != NULL);

	retval = get_retval_register();
	reset_register(retval);
	retval->type = table_m;
	retval->data.tableVal = table;
	inc_table_refcounter(table);
}

void set_number_memcell(avm_memcell *memcell, double value) {
	assert(memcell != NULL);

	clear_memcell(memcell);
	memcell->type = number_m;
	memcell->data.numVal = value;
}

void set_string_memcell(avm_memcell *memcell, const char *value) {
	assert(memcell != NULL);
	assert(value != NULL);

	clear_memcell(memcell);
	memcell->type = string_m;
	memcell->data.strVal = strdup(value);
	assert(memcell->data.strVal != NULL);
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
