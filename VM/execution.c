#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "execution.h"

static void execute_unsupported(const avm_instruction *instruction);
static void execute_arithmetic(const avm_instruction *instruction, int opcode);
static void execute_relational(const avm_instruction *instruction, int opcode);

static execute_func_t execute_dispatch[] = {
	execute_assign,
	execute_add,
	execute_sub,
	execute_mul,
	execute_div,
	execute_mod,
	execute_unsupported,
	execute_unsupported,
	execute_unsupported,
	execute_unsupported,
	execute_jeq,
	execute_jne,
	execute_jle,
	execute_jge,
	execute_jlt,
	execute_jgt,
	execute_jump,
	execute_call,
	execute_pusharg,
	execute_funcstart,
	execute_funcend,
	execute_unsupported,
	execute_unsupported,
	execute_unsupported,
	execute_nop
};

void execute_cycle() {

	avm_binary *binary;

	binary = get_program_binary();
	assert(binary != NULL);

	while(!get_execution_finished()) {
		if(get_pc() < 0 || get_pc() >= binary->instruction_count) {
			set_execution_finished(True);
			break;
		}

		execute_current_instruction();
	}
}

void execute_current_instruction() {
	
	avm_binary *binary;
	const avm_instruction *instruction;

	binary = get_program_binary();
	
	assert(binary != NULL);
	assert(get_pc() >= 0);
	assert(get_pc() < binary->instruction_count);

	instruction = &binary->instructions[get_pc()];

	assert(instruction->opcode >= 0);
	assert(instruction->opcode <= nop_v);

	execute_dispatch[instruction->opcode](instruction);
}

void execute_assign(const avm_instruction *instruction) {

	avm_memcell *left_memcell;
	avm_memcell *right_memcell;

	assert(instruction != NULL);

	left_memcell = translate_operand(&instruction->result, NULL);
	right_memcell = translate_operand(&instruction->arg1, get_ax_register());

	assert(left_memcell != NULL);
	assert(right_memcell != NULL);

	assign_memcell(left_memcell, right_memcell);
	set_pc(get_pc() + 1);
}

void execute_add(const avm_instruction *instruction) {
	execute_arithmetic(instruction, add_v);
}

void execute_sub(const avm_instruction *instruction) {
	execute_arithmetic(instruction, sub_v);
}

void execute_mul(const avm_instruction *instruction) {
	execute_arithmetic(instruction, mul_v);
}

void execute_div(const avm_instruction *instruction) {
	execute_arithmetic(instruction, div_v);
}

void execute_mod(const avm_instruction *instruction) {
	execute_arithmetic(instruction, mod_v);
}

void execute_jeq(const avm_instruction *instruction) {
	
	avm_memcell *left_memcell;
	avm_memcell *right_memcell;

	assert(instruction != NULL);
	assert(instruction->result.type == label_a);

	left_memcell = translate_operand(&instruction->arg1, get_ax_register());
	right_memcell = translate_operand(&instruction->arg2, get_bx_register());

	assert(left_memcell != NULL);
	assert(right_memcell != NULL);

	if(are_equal(left_memcell, right_memcell))
		set_pc((int) instruction->result.val);
	else
		set_pc(get_pc() + 1);
}

void execute_jne(const avm_instruction *instruction) {
	
	avm_memcell *left_memcell;
	avm_memcell *right_memcell;

	assert(instruction != NULL);
	assert(instruction->result.type == label_a);

	left_memcell = translate_operand(&instruction->arg1, get_ax_register());
	right_memcell = translate_operand(&instruction->arg2, get_bx_register());

	assert(left_memcell != NULL);
	assert(right_memcell != NULL);

	if(!are_equal(left_memcell, right_memcell))
		set_pc((int) instruction->result.val);
	else
		set_pc(get_pc() + 1);
}

void execute_jle(const avm_instruction *instruction) {
	execute_relational(instruction, jle_v);
}

void execute_jge(const avm_instruction *instruction) {
	execute_relational(instruction, jge_v);
}

void execute_jlt(const avm_instruction *instruction) {
	execute_relational(instruction, jlt_v);
}

void execute_jgt(const avm_instruction *instruction) {
	execute_relational(instruction, jgt_v);
}

void execute_jump(const avm_instruction *instruction) {
	
	avm_binary *binary;

	assert(instruction != NULL);
	assert(instruction->result.type == label_a);

	binary = get_program_binary();
	assert(binary != NULL);
	assert((int) instruction->result.val >= 0);
	assert((int) instruction->result.val <= binary->instruction_count);

	set_pc((int) instruction->result.val);
}

void execute_call(const avm_instruction *instruction) {

	avm_memcell *function_memcell;

	assert(instruction != NULL);

	function_memcell = translate_operand(&instruction->arg1, get_ax_register());
	assert(function_memcell != NULL);

	if(function_memcell->type == userfunc_m) {
		save_call_environment();
		reset_total_actuals();
		set_pc(function_memcell->data.funcVal);
	}
	else if(function_memcell->type == libfunc_m) {
		save_call_environment();
		reset_total_actuals();
		set_topsp(get_top());
		call_library_function(function_memcell->data.libfuncVal);
	}
	else
		assert(0);
}

void execute_pusharg(const avm_instruction *instruction) {

	avm_memcell *actual_argument;

	assert(instruction != NULL);
	assert(stack != NULL);
	assert(get_top() >= 0);
	assert(get_top() < STACK_SIZE);

	actual_argument = translate_operand(&instruction->arg1, get_ax_register());
	assert(actual_argument != NULL);

	assign_memcell(&stack[get_top()], actual_argument);
	set_top(get_top() - 1);
	inc_total_actuals();
	set_pc(get_pc() + 1);
}

void execute_funcstart(const avm_instruction *instruction) {

	avm_binary *binary;
	int userfunc_index;
	int local_size;

	assert(instruction != NULL);
	assert(instruction->result.type == userfunc_a);

	binary = get_program_binary();
	assert(binary != NULL);

	userfunc_index = (int) instruction->result.val;
	assert(userfunc_index >= 0);
	assert(userfunc_index < binary->userfunc_count);

	local_size = binary->userfuncs[userfunc_index].localSize;
	assert(local_size >= 0);

	set_topsp(get_top());
	set_top(get_top() - local_size);
	reset_total_actuals();
	set_pc(get_pc() + 1);
}

void execute_funcend(const avm_instruction *instruction) {

	int old_top;
	int old_topsp;
	int saved_top;
	int saved_topsp;
	int saved_pc;
	int saved_actuals;
	int i;
	int function_stack;

	old_top = get_top();
	old_topsp = get_topsp();

	assert(old_top >= 0);
	assert(old_topsp >= 0);
	assert(old_topsp < STACK_SIZE);

	saved_topsp = get_env_value(old_topsp, SAVEDTOPSP_OFFSET);
	saved_top = get_env_value(old_topsp, SAVEDTOP_OFFSET);
	saved_pc = get_env_value(old_topsp, SAVEDPC_OFFSET);
	saved_actuals = get_env_value(old_topsp, NUMACTUALS_OFFSET);

	assert(saved_actuals >= 0);
	
	function_stack = old_topsp + STACKENV_SIZE + saved_actuals;
	assert(function_stack >= 0);
	assert(function_stack < STACK_SIZE);

	for(i = old_top + 1; i <= function_stack; i++)
		clear_memcell(&stack[i]);

	set_top(saved_top);
	set_topsp(saved_topsp);
	reset_total_actuals();
	set_pc(saved_pc);
}

void execute_nop(const avm_instruction *instruction) {
	set_pc(get_pc() + 1);
}

static void execute_unsupported(const avm_instruction *instruction) {
	runtime_error("unsupported instruction");
}

static void execute_arithmetic(const avm_instruction *instruction, int opcode) {
	
	avm_memcell *left_memcell;
	avm_memcell *right_memcell_1;
	avm_memcell *right_memcell_2;
	double result;

	assert(instruction != NULL);
	assert(opcode == add_v || opcode == sub_v || opcode == mul_v || opcode == div_v || opcode == mod_v);

	left_memcell = translate_operand(&instruction->result, NULL);
	right_memcell_1 = translate_operand(&instruction->arg1, get_ax_register());
	right_memcell_2 = translate_operand(&instruction->arg2, get_bx_register());

	assert(left_memcell != NULL);
	assert(right_memcell_1 != NULL);
	assert(right_memcell_2 != NULL);

	if(right_memcell_1->type != number_m || right_memcell_2->type != number_m) {
		runtime_error("arithmetic operands must be numbers");
		return;
	}

	switch(opcode) {
		case add_v:
			result = right_memcell_1->data.numVal + right_memcell_2->data.numVal;
			break;
		case sub_v:
			result = right_memcell_1->data.numVal - right_memcell_2->data.numVal;
			break;
		case mul_v:
			result = right_memcell_1->data.numVal * right_memcell_2->data.numVal;
			break;
		case div_v:
			if(right_memcell_2->data.numVal == 0) {
				runtime_error("division by zero");
				return;
			}

			result = right_memcell_1->data.numVal / right_memcell_2->data.numVal;
			break;
		case mod_v:
			if(right_memcell_2->data.numVal == 0) {
				runtime_error("modulo by zero");
				return;
			}

			result = remainder(right_memcell_1->data.numVal, right_memcell_2->data.numVal);
			break;
		default:
			assert(0);
	}

	clear_memcell(left_memcell);
	left_memcell->type = number_m;
	left_memcell->data.numVal = result;

	if(!get_execution_finished())
		set_pc(get_pc() + 1);
}

static void execute_relational(const avm_instruction *instruction, int opcode) {
	
	avm_memcell *left_memcell;
	avm_memcell *right_memcell;
	int comparison_result;

	assert(instruction != NULL);
	assert(opcode == jle_v || opcode == jge_v || opcode == jlt_v || opcode == jgt_v);
	assert(instruction->result.type == label_a);

	left_memcell = translate_operand(&instruction->arg1, get_ax_register());
	right_memcell = translate_operand(&instruction->arg2, get_bx_register());

	assert(left_memcell != NULL);
	assert(right_memcell != NULL);

	if(left_memcell->type != number_m || right_memcell->type != number_m) {
		runtime_error("relational operands must be numbers");
		return;
	}

	switch(opcode) {
		case jle_v:
			comparison_result = left_memcell->data.numVal <= right_memcell->data.numVal;
			break;
		case jge_v:
			comparison_result = left_memcell->data.numVal >= right_memcell->data.numVal;
			break;
		case jlt_v:
			comparison_result = left_memcell->data.numVal < right_memcell->data.numVal;
			break;
		case jgt_v:
			comparison_result = left_memcell->data.numVal > right_memcell->data.numVal;
			break;
		default:
			assert(0);
	}

	if(comparison_result)
		set_pc((int) instruction->result.val);
	else
		set_pc(get_pc() + 1);
}
