#include <assert.h>
#include <stddef.h>

#include "avm_state.h"

static avm_binary *program_binary = NULL;

static int pc = 0;
static int top = 0;
static int topsp = 0;
static int execution_finished = 0;
static int total_globals = 0;

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
	execution_finished = False;

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
	execution_finished = False;
	total_globals = 0;

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
        assert(total_globals >= 0);

        return total_globals;
}

int get_pc() {
	assert(pc >= 0);
	
	return pc;
}

void set_pc(int new_pc) {
	assert(new_pc >= 0);

	pc = new_pc;
}

int get_top() {
	assert(top >= 0);
	
	return top;
}

void set_top(int new_top) {
	assert(new_top >= 0);
	assert(new_top < STACK_SIZE);
	
	top = new_top;
}

int get_topsp() {
	assert(topsp >= 0);
	
	return topsp;
}

void set_topsp(int new_topsp) {
	assert(new_topsp >= 0);
	assert(new_topsp < STACK_SIZE);
	
	topsp = new_topsp;
}

int get_execution_finished() {
	assert(execution_finished == True || execution_finished == False);
	
	return execution_finished;
}

void set_execution_finished(int finished) {
	assert(finished == True || finished == False);
	
	execution_finished = finished;
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

