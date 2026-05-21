#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdio.h>

typedef enum iopcode {
	assign_i,
	add_i,
	sub_i,
	mul_i,
	div_i,
	mod_i,
	uminus_i,
	and_i,
	or_i,
	not_i,
	jeq_i,
	jne_i,
	jle_i,
	jge_i,
	jlt_i,
	jgt_i,
	jump_i,
	call_i,
	pusharg_i,
	funcenter_i,
	funcexit_i,
	newtable_i,
	tablegetelem_i,
	tablesetelem_i,
	nop_i
} iopcode;

typedef enum ioperand_type {
	label_o,
	global_o,
	formal_o,
	local_o,
	number_o,
	string_o,
	bool_o,
	nil_o,
	userfunc_o,
	libfunc_o,
	retval_o,
	unused_o
} ioperand_type;

typedef struct ioperand {
	ioperand_type type;
	unsigned val;
} ioperand;

typedef struct Instruction {
	iopcode opcode;
	ioperand result;
	ioperand arg1;
	ioperand arg2;
	int src_line;
} Instruction;

typedef struct UserFunc {
	unsigned address;
	unsigned localSize;
	char *name;
} UserFunc;

Instruction* create_instruction(iopcode opcode, ioperand result, ioperand arg1, ioperand arg2, int src_line);

void add_instruction(Instruction instruction);

void expand_instructions();

Instruction* get_instructions();

int get_instruction_count();

int next_instruction_label();

char* iopcode_to_string(iopcode opcode);

void print_instructions(FILE *f);

void free_instructions();

#endif
