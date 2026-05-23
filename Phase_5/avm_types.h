#ifndef AVM_TYPES_H
#define AVM_TYPES_H

typedef enum avm_opcode {
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
} avm_opcode;

typedef enum avm_operand_type {
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
} avm_operand_type;

typedef enum avm_memcell_type {
	number_m,
	string_m,
	bool_m,
	table_m,
	userfunc_m,
	libfunc_m,
	nil_m,
	undef_m
} avm_memcell_type;

typedef struct avm_operand {
	int type;
	unsigned val;
} avm_operand;

typedef struct avm_instruction {
	int opcode;
	avm_operand result;
	avm_operand arg1;
	avm_operand arg2;
	int src_line;
} avm_instruction;

typedef struct avm_userfunc {
	int address;
	int localSize;
	char *name;
} avm_userfunc;

typedef struct avm_binary {
	unsigned magic;

	int string_count;
	char **string_consts;

	int number_count;
	double *number_consts;

	int userfunc_count;
	avm_userfunc *userfuncs;

	int libfunc_count;
	char **libfuncs;

	int instruction_count;
	avm_instruction *instructions;
} avm_binary;

#endif
