#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib_func.h"

static int get_library_function_id(const char *name);
static int get_current_total_actuals(void);
static avm_memcell *get_actual(int index);
static int get_caller_topsp(void);
static void set_retval_nil(void);
static void restore_after_libfunc_call(void);
static void print_memcell_value(const avm_memcell *memcell);

void call_library_function(const char *name) {
	
	int function_id;

	assert(name != NULL);

	function_id = get_library_function_id(name);

	switch(function_id) {
		case LIBFUNC_PRINT:
			libfunc_print();
			break;

		case LIBFUNC_TYPEOF:
			libfunc_typeof();
			break;

		case LIBFUNC_TOTALARGUMENTS:
			libfunc_totalarguments();
			break;

		case LIBFUNC_ARGUMENT:
			libfunc_argument();
			break;

		case LIBFUNC_UNSUPPORTED:
			runtime_error("unsupported library function");
			break;

		default:
			assert(0);
	}

	if(!get_execution_finished())
		restore_after_libfunc_call();
}

void libfunc_print() {
	
	int i, total_actuals;

	total_actuals = get_current_total_actuals();

	for(i = 0; i < total_actuals; i++)
		print_memcell_value(get_actual(i));

	set_retval_nil();
}

void libfunc_typeof() {
	
	avm_memcell *retval;
	avm_memcell *actual;
	const char *type_string;

	if(get_current_total_actuals() != 1) {
		runtime_error("typeof expects exactly one argument");
		return;
	}

	actual = get_actual(0);
	assert(actual != NULL);

	switch(actual->type) {
		case bool_m:
			type_string = "boolean";
			break;
		case number_m:
			type_string = "number";
			break;
		case string_m:
			type_string = "string";
			break;
		case nil_m:
			type_string = "nil";
			break;
		case userfunc_m:
			type_string = "userfunction";
			break;
		case libfunc_m:
			type_string = "libraryfunction";
			break;
		case table_m:
			type_string = "table";
			break;
		case undef_m:
			type_string = "undefined";
			break;
		default:
			assert(0);
	}

	retval = get_retval_register();
	reset_register(retval);
	retval->type = string_m;
	retval->data.strVal = strdup(type_string);
	assert(retval->data.strVal != NULL);
}

void libfunc_totalarguments() {
	
	avm_memcell *retval;
	int caller_topsp;

	retval = get_retval_register();
	reset_register(retval);

	caller_topsp = get_caller_topsp();
	if(caller_topsp == get_global_topsp()) {
		retval->type = nil_m;
		return;
	}

	retval->type = number_m;
	retval->data.numVal = get_env_value(caller_topsp, NUMACTUALS_OFFSET);
}

void libfunc_argument(void) {
	
	avm_memcell *retval;
	avm_memcell *index_memcell;
	int caller_topsp;
	int index;
	int caller_total_actuals;
	int stack_index;

	if(get_current_total_actuals() != 1) {
		runtime_error("argument expects exactly one argument");
		return;
	}

	retval = get_retval_register();
	reset_register(retval);

	caller_topsp = get_caller_topsp();
	if(caller_topsp == get_global_topsp()) {
		retval->type = nil_m;
		return;
	}

	index_memcell = get_actual(0);
	assert(index_memcell != NULL);

	if(index_memcell->type != number_m) {
		runtime_error("argument index must be a number");
		return;
	}

	index = (int) index_memcell->data.numVal;
	caller_total_actuals = get_env_value(caller_topsp, NUMACTUALS_OFFSET);

	if(index < 0 || index >= caller_total_actuals) {
		retval->type = nil_m;
		return;
	}

	stack_index = caller_topsp + STACKENV_SIZE + 1 + index;
	assert(stack_index >= 0);
	assert(stack_index < STACK_SIZE);

	assign_memcell(retval, &stack[stack_index]);
}

static int get_current_total_actuals() {
	return get_env_value(get_topsp(), NUMACTUALS_OFFSET);
}

static int get_library_function_id(const char *name) {
	assert(name != NULL);

	if(strcmp(name, "print") == 0)
		return LIBFUNC_PRINT;

	if(strcmp(name, "typeof") == 0)
		return LIBFUNC_TYPEOF;

	if(strcmp(name, "totalarguments") == 0)
		return LIBFUNC_TOTALARGUMENTS;

	if(strcmp(name, "argument") == 0)
		return LIBFUNC_ARGUMENT;

	return LIBFUNC_UNSUPPORTED;
}

static avm_memcell *get_actual(int index) {
	
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

static int get_caller_topsp(void) {
	return get_env_value(get_topsp(), SAVEDTOPSP_OFFSET);
}

static void set_retval_nil(void) {
	avm_memcell *retval;

	retval = get_retval_register();
	reset_register(retval);
	retval->type = nil_m;
}

static void restore_after_libfunc_call() {
	
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

static void print_memcell_value(const avm_memcell *memcell) {
	assert(memcell != NULL);

	switch(memcell->type) {
		case bool_m:
			printf(memcell->data.boolVal ? "true" : "false");
			break;
		case number_m:
			printf("%.3f", memcell->data.numVal);
			break;
		case string_m:
			printf("%s", memcell->data.strVal);
			break;
		case nil_m:
			printf("nil");
			break;
		case userfunc_m:
			printf("user function %d", memcell->data.funcVal);
			break;
		case libfunc_m:
			printf("library function %s", memcell->data.libfuncVal);
			break;
		case table_m:
			printf("table");
			break;
		case undef_m:
			printf("undefined");
			break;
		default:
			assert(0);
	}
}
