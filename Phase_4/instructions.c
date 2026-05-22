#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "instructions.h"
#include "const_tables.h"

static int count = 0;
static int capacity = 0;
static Instruction *Instructions = NULL;

static void operand_to_text(ioperand operand, char *buffer, size_t size);

Instruction* create_instruction(iopcode opcode, ioperand result, ioperand arg1, ioperand arg2, int src_line) {
	
	Instruction *instruction = malloc(sizeof(Instruction));

	assert(instruction != NULL);

	instruction->opcode = opcode;
	instruction->result = result;
	instruction->arg1 = arg1;
	instruction->arg2 = arg2;
	instruction->src_line = src_line;

	return instruction;
}

void new_instruction(Instruction instruction) {
	
	if(count >= capacity)
		expand_instructions();

	Instructions[count] = instruction;
	count++;
}

void expand_instructions() {

	Instruction *tmpInstructions;

	capacity += 128;
	tmpInstructions = realloc(Instructions, capacity * sizeof(Instruction));
	assert(tmpInstructions != NULL);

	Instructions = tmpInstructions;
}

Instruction* get_instructions() {
	return Instructions;
}

int get_instruction_count() {
	return count;
}

char* iopcode_to_string(iopcode opcode) {
	switch(opcode) {
		case assign_i:		return "assign";
		case add_i:		return "add";
		case sub_i:		return "sub";
		case mul_i:		return "mul";
		case div_i:		return "div";
		case mod_i:		return "mod";
		case uminus_i:		return "uminus";
		case and_i:		return "and";
		case or_i:		return "or";
		case not_i:		return "not";
		case jeq_i:		return "jeq";
		case jne_i:		return "jne";
		case jle_i:		return "jle";
		case jge_i:		return "jge";
		case jlt_i:		return "jlt";
		case jgt_i:		return "jgt";
		case jump_i:		return "jump";
		case call_i:		return "call";
		case pusharg_i:		return "pusharg";
		case funcenter_i:	return "funcenter";
		case funcexit_i:	return "funcexit";
		case newtable_i:	return "newtable";
		case tablegetelem_i:	return "tablegetelem";
		case tablesetelem_i:	return "tablesetelem";
		case nop_i:		return "nop";
		default:		return NULL;
	}
}

void print_instructions_text(FILE *f) {
	
	int i;
	char result_buf[32];
	char arg1_buf[32];
	char arg2_buf[32];

	assert(f != NULL);

	fprintf(f, "\n--- STRING CONSTS ---\n");
	char **string_consts = get_string_consts();
	for(i = 0; i < get_string_count(); i++)
		fprintf(f, "%d: \"%s\"\n", i, string_consts[i]);

	fprintf(f, "\n--- NUMBER CONSTS ---\n");
	double *number_consts = get_number_consts();
        for(i = 0; i < get_number_count(); i++)
                fprintf(f, "%d: %f\n", i, number_consts[i]);	

	fprintf(f, "\n--- LIBRARY FUNCTIONS ---\n");
	char **libfunc_consts = get_libfunc_consts();
	for(i = 0; i < get_libfunc_count(); i++)
		fprintf(f, "%d: %s\n", i, libfunc_consts[i]);

	fprintf(f, "\n--- USER FUNCTIONS ---\n");
        UserFunc *user_funcs = get_userfunc_consts();
        for(i = 0; i < get_userfunc_count(); i++)
                fprintf(f, "%d: name=%s, address=%d, localSize=%d\n", i, user_funcs[i].name, user_funcs[i].address, user_funcs[i].localSize);

	fprintf(f, "\n--- INSTRUCTIONS ---\n");
	fprintf(f, "%-8s %-15s %-20s %-20s %-20s\n", "instr#", "opcode", "result", "arg1", "arg2");
	fprintf(f, "-----------------------------------------------------------------------------\n");

	for(i = 0; i < count; i++) {
		operand_to_text(Instructions[i].result, result_buf, sizeof(result_buf));
		operand_to_text(Instructions[i].arg1, arg1_buf, sizeof(arg1_buf));
		operand_to_text(Instructions[i].arg2, arg2_buf, sizeof(arg2_buf));

		fprintf(f, "%-8d %-15s %-20s %-20s %-20s\n", i, iopcode_to_string(Instructions[i].opcode), result_buf, arg1_buf, arg2_buf);
	}

	fprintf(f, "-----------------------------------------------------------------------------\n");
}

void free_instructions() {
	
	free(Instructions);
	Instructions = NULL;
	count = 0;
	capacity = 0;
}

static void operand_to_text(ioperand operand, char *buffer, size_t size) {
	
	assert(buffer != NULL);
	assert(size > 0);

	switch(operand.type) {
		case label_o:
			snprintf(buffer, size, "label %u", operand.val);
			break;
		case global_o:
			snprintf(buffer, size, "global %u", operand.val);
			break;
		case formal_o:
			snprintf(buffer, size, "formal %u", operand.val);
			break;
		case local_o:
			snprintf(buffer, size, "local %u", operand.val);
			break;
		case number_o:
			snprintf(buffer, size, "number %u", operand.val);
			break;
		case string_o:
			snprintf(buffer, size, "string %u", operand.val);
			break;
		case bool_o:
			snprintf(buffer, size, "bool %u", operand.val);
			break;
		case nil_o:
			snprintf(buffer, size, "nil");
			break;
		case userfunc_o:
			snprintf(buffer, size, "userfunc %u", operand.val);
			break;
		case libfunc_o:
			snprintf(buffer, size, "libfunc %u", operand.val);
			break;
		case retval_o:
			snprintf(buffer, size, "retval");
			break;
		case unused_o:
			snprintf(buffer, size, "-");
			break;
		default:
			snprintf(buffer, size, "?");
			break;
	}
}
