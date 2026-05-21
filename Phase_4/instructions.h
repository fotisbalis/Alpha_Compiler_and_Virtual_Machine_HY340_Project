#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

typedef enum vmopcode {
	assign_v,
	add_v,
	sub_v,
	mul_v,
	div_v,
	mod_v,
	uminus_v,
	and_v,
	or_v,
	not_v,
	jeq_v,
	jne_v,
	jle_v,
	jge_v,
	jlt_v,
	jgt_v,
	jump_v,
	call_v,
	pusharg_v,
	funcenter_v,
	funcexit_v,
	newtable_v,
	tablegetelem_v,
	tablesetelem_v,
	nop_v
} vmopcode;

typedef enum vmarg_type {
	label_a,
	global_a,
	formal_a,
	local_a,
	number_a,
	string_a,
	bool_a,
	nil_a,
	userfunc_a,
	libfunc_a,
	retval_a,
	unused_a
} vmarg_type;

typedef struct vmarg {
	vmarg_type type;
	unsigned val;
} vmarg;

typedef struct Instruction {
	vmopcode opcode;
	vmarg result;
	vmarg arg1;
	vmarg arg2;
	int line;
} Instruction;

typedef struct UserFunc {
	unsigned address;
	unsigned localSize;
	char *id;
} UserFunc;

#endif
