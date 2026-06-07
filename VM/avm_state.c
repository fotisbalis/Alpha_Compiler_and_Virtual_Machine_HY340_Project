#include <assert.h>
#include <stddef.h>

#include "headers/avm_state.h"

static avm_binary *program_binary = NULL;

static int pc = 0;
static int top = 0;
static int topsp = 0;
static int global_topsp = 0;
static int execution_finished = 0;
static int total_globals = 0;
static int total_actuals = 0;

static avm_memcell retval;
static avm_memcell ax;
static avm_memcell bx;
static avm_memcell cx;

static int calulate_binary_global_count(avm_binary *binary);

void initialize_avm_state(avm_binary *binary) {
	
	assert(binary != NULL);

	program_binary = binary;

	create_stack();
	total_globals = calulate_binary_global_count(binary);

	assert(total_globals >= 0);
	assert(total_globals < STACK_SIZE);

	pc = 0;
	top = (STACK_SIZE - 1) - total_globals;
	topsp = top;
	global_topsp = topsp;
	execution_finished = False;
	total_actuals = 0;

	reset_register(&retval);
	reset_register(&ax);
	reset_register(&bx);
	reset_register(&cx);
}

void reset_avm_state() {
	
	program_binary = NULL;

	reset_stack();

	pc = 0;
	top = 0;
	topsp = 0;
	global_topsp = 0;
	execution_finished = False;
	total_globals = 0;
	total_actuals = 0;

	reset_register(&retval);
	reset_register(&ax);
	reset_register(&bx);
	reset_register(&cx);
}

void reset_register(avm_memcell *memcell) {
        assert(memcell != NULL);

        clear_memcell(memcell);
        memcell->type = undef_m;
}

avm_binary *get_program_binary() {
	return program_binary;
}

int get_global_count() {
        return total_globals;
}

int get_pc() {
	return pc;
}

void set_pc(int new_pc) {
	assert(new_pc >= 0);

	pc = new_pc;
}

int get_top() {
	return top;
}

void set_top(int new_top) {
	assert(new_top >= 0);
	assert(new_top < STACK_SIZE);
	
	top = new_top;
}

int get_topsp() {
	return topsp;
}

void set_topsp(int new_topsp) {
	assert(new_topsp >= 0);
	assert(new_topsp < STACK_SIZE);
	
	topsp = new_topsp;
}

int get_global_topsp(void) {
	return global_topsp;
}

int get_execution_finished() {
	return execution_finished;
}

void set_execution_finished(int finished) {
	assert(finished == True || finished == False);
	
	execution_finished = finished;
}

int get_total_actuals() {
	return total_actuals;
}

void inc_total_actuals() {
	total_actuals++;
}

void reset_total_actuals() {
	total_actuals = 0;
}

void push_env_value(int value) {
	
	assert(stack != NULL);
	assert(get_top() >= 0);
	assert(get_top() < STACK_SIZE);

	clear_memcell(&stack[get_top()]);
	
	stack[get_top()].type = number_m;
	stack[get_top()].data.numVal = value;
	
	set_top(get_top() - 1);
}

int get_env_value(int current_topsp, int offset) {
	
	int stack_index;

	assert(stack != NULL);
	assert(current_topsp >= 0);
	assert(current_topsp < STACK_SIZE);
	assert(offset >= 0);

	stack_index = current_topsp + offset;
	
	assert(stack_index >= 0);
	assert(stack_index < STACK_SIZE);
	assert(stack[stack_index].type == number_m);

	return (int) stack[stack_index].data.numVal;
}

void save_call_environment() {
	
	push_env_value(get_total_actuals());
	push_env_value(get_pc() + 1);
	push_env_value(get_top() + get_total_actuals() + 2);
	push_env_value(get_topsp());
}

avm_memcell *get_retval_register() {
	return &retval;
}

avm_memcell *get_ax_register() {
	return &ax;
}

avm_memcell *get_bx_register() {
	return &bx;
}

avm_memcell *get_cx_register() {
	return &cx;
}

static int calulate_binary_global_count(avm_binary *binary) {

	int i;
	int max_global_offset;
	const avm_instruction *instruction;

	assert(binary != NULL);

	max_global_offset = -1;

	for(i = 0; i < binary->instruction_count; i++) {
		instruction = &binary->instructions[i];

		if(instruction->result.type == global_a && (int)instruction->result.val > max_global_offset)
			max_global_offset = (int) instruction->result.val;

		if(instruction->arg1.type == global_a && (int)instruction->arg1.val > max_global_offset)
			max_global_offset = (int) instruction->arg1.val;

		if(instruction->arg2.type == global_a && (int)instruction->arg2.val > max_global_offset)
			max_global_offset = (int) instruction->arg2.val;
	}

	return max_global_offset + 1;
}
