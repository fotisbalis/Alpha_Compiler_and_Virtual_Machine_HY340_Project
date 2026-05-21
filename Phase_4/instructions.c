#include <assert.h>
#include <stdlib.h>

#include "instructions.h"

static int count = 0;
static int capacity = 0;
static Instruction *Instructions = NULL;

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

void print_instructions(FILE *f) {
	
	int i;

	assert(f != NULL);

	fprintf(f, "%-8s %-15s %-15s %-15s %-15s %s", "instr#", "opcode", "result", "arg1", "arg2", "src_line");
	fprintf(f, "\n--------------------------------------------------------------------------------\n");

	for(i = 0; i < count; i++) {
		fprintf(
			f,
			"%-8d %-15s (%d,%u)         (%d,%u)         (%d,%u)         %d\n",
			i,
			iopcode_to_string(Instructions[i].opcode),
			Instructions[i].result.type, Instructions[i].result.val,
			Instructions[i].arg1.type, Instructions[i].arg1.val,
			Instructions[i].arg2.type, Instructions[i].arg2.val,
			Instructions[i].src_line
		);
	}

	fprintf(f, "--------------------------------------------------------------------------------\n");
}

void free_instructions() {
	
	free(Instructions);
	Instructions = NULL;
	count = 0;
	capacity = 0;
}
