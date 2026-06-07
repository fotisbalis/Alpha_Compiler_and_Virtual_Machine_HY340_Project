#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/binary_loader.h"

static unsigned read_unsigned(FILE *fp);
static int read_int(FILE *fp);
static double read_double(FILE *fp);
static char *read_string(FILE *fp);
static void operand_to_text(avm_operand operand, char *buffer, size_t size);

const char *avm_opcode_to_string(int opcode) {
	
	switch(opcode) {
		case assign_v: return "assign";
		case add_v: return "add";
		case sub_v: return "sub";
		case mul_v: return "mul";
		case div_v: return "div";
		case mod_v: return "mod";
		case uminus_v: return "uminus";
		case and_v: return "and";
		case or_v: return "or";
		case not_v: return "not";
		case jeq_v: return "jeq";
		case jne_v: return "jne";
		case jle_v: return "jle";
		case jge_v: return "jge";
		case jlt_v: return "jlt";
		case jgt_v: return "jgt";
		case jump_v: return "jump";
		case call_v: return "call";
		case pusharg_v: return "pusharg";
		case funcenter_v: return "funcenter";
		case funcexit_v: return "funcexit";
		case newtable_v: return "newtable";
		case tablegetelem_v: return "tablegetelem";
		case tablesetelem_v: return "tablesetelem";
		case nop_v: return "nop";
		default: return "unknown";
	}
}

const char *avm_operand_type_to_string(int type) {
	
	switch(type) {
		case label_a: return "label";
		case global_a: return "global";
		case formal_a: return "formal";
		case local_a: return "local";
		case number_a: return "number";
		case string_a: return "string";
		case bool_a: return "bool";
		case nil_a: return "nil";
		case userfunc_a: return "userfunc";
		case libfunc_a: return "libfunc";
		case retval_a: return "retval";
		case unused_a: return "-";
		default: return "?";
	}
}

avm_binary *binary_load(FILE *fp) {
	
	int i;
	avm_binary *binary;

	assert(fp != NULL);

	binary = calloc(1, sizeof(avm_binary));
	assert(binary != NULL);

	binary->magic = read_unsigned(fp);
	assert(binary->magic == AVM_BINARY_MAGIC);

	binary->string_count = read_int(fp);
	assert(binary->string_count >= 0);
	
	if(binary->string_count > 0) {
		
		binary->string_consts = malloc(binary->string_count * sizeof(char *));
		assert(binary->string_consts != NULL);
		
		for(i = 0; i < binary->string_count; i++)
			binary->string_consts[i] = read_string(fp);
	}

	binary->number_count = read_int(fp);
	assert(binary->number_count >= 0);
	
	if(binary->number_count > 0) {
		
		binary->number_consts = malloc(binary->number_count * sizeof(double));
		assert(binary->number_consts != NULL);
		
		for(i = 0; i < binary->number_count; i++)
			binary->number_consts[i] = read_double(fp);
	}

	binary->userfunc_count = read_int(fp);
	assert(binary->userfunc_count >= 0);
	
	if(binary->userfunc_count > 0) {
		
		binary->userfuncs = malloc(binary->userfunc_count * sizeof(avm_userfunc));
		assert(binary->userfuncs != NULL);
		
		for(i = 0; i < binary->userfunc_count; i++) {
			binary->userfuncs[i].address = read_int(fp);
			binary->userfuncs[i].localSize = read_int(fp);
			binary->userfuncs[i].name = read_string(fp);
		}
	}

	binary->libfunc_count = read_int(fp);
	assert(binary->libfunc_count >= 0);
	
	if(binary->libfunc_count > 0) {
		
		binary->libfuncs = malloc(binary->libfunc_count * sizeof(char *));
		assert(binary->libfuncs != NULL);
		
		for(i = 0; i < binary->libfunc_count; i++)
			binary->libfuncs[i] = read_string(fp);
	}

	binary->instruction_count = read_int(fp);
	assert(binary->instruction_count >= 0);
	
	if(binary->instruction_count > 0) {
		
		binary->instructions = malloc(binary->instruction_count * sizeof(avm_instruction));
		assert(binary->instructions != NULL);
		
		for(i = 0; i < binary->instruction_count; i++) {
			binary->instructions[i].opcode = read_int(fp);
			binary->instructions[i].result.type = read_int(fp);
			binary->instructions[i].result.val = read_unsigned(fp);
			binary->instructions[i].arg1.type = read_int(fp);
			binary->instructions[i].arg1.val = read_unsigned(fp);
			binary->instructions[i].arg2.type = read_int(fp);
			binary->instructions[i].arg2.val = read_unsigned(fp);
			binary->instructions[i].src_line = read_int(fp);
		}
	}

	return binary;
}

avm_binary *binary_load_from_path(const char *path) {
	
	FILE *fp;
	avm_binary *binary;

	assert(path != NULL);

	fp = fopen(path, "rb");
	assert(fp != NULL);

	binary = binary_load(fp);
	fclose(fp);

	return binary;
}

void binary_print(FILE *fp, const avm_binary *binary) {
	
	int i;
	char result_buf[32];
	char arg1_buf[32];
	char arg2_buf[32];

	assert(fp != NULL);
	assert(binary != NULL);

	fprintf(fp, "MAGIC NUMBER: %u\n", binary->magic);

	fprintf(fp, "\n--- STRING CONSTS ---\n");
	for(i = 0; i < binary->string_count; i++)
		fprintf(fp, "%d: \"%s\"\n", i, binary->string_consts[i]);

	fprintf(fp, "\n--- NUMBER CONSTS ---\n");
	for(i = 0; i < binary->number_count; i++)
		fprintf(fp, "%d: %f\n", i, binary->number_consts[i]);

	fprintf(fp, "\n--- USER FUNCTIONS ---\n");
	for(i = 0; i < binary->userfunc_count; i++) {
		fprintf(
			fp,
			"%d: name=%s, address=%d, localSize=%d\n",
			i,
			binary->userfuncs[i].name,
			binary->userfuncs[i].address,
			binary->userfuncs[i].localSize
		);
	}

	fprintf(fp, "\n--- LIBRARY FUNCTIONS ---\n");
	for(i = 0; i < binary->libfunc_count; i++)
		fprintf(fp, "%d: %s\n", i, binary->libfuncs[i]);

	fprintf(fp, "\n--- INSTRUCTIONS ---\n");
	fprintf(fp, "%-8s %-15s %-20s %-20s %-20s\n", "instr#", "opcode", "result", "arg1", "arg2");
	fprintf(fp, "-----------------------------------------------------------------------------\n");

	for(i = 0; i < binary->instruction_count; i++) {
		operand_to_text(binary->instructions[i].result, result_buf, sizeof(result_buf));
		operand_to_text(binary->instructions[i].arg1, arg1_buf, sizeof(arg1_buf));
		operand_to_text(binary->instructions[i].arg2, arg2_buf, sizeof(arg2_buf));

		fprintf(
			fp,
			"%-8d %-15s %-20s %-20s %-20s\n",
			i,
			avm_opcode_to_string(binary->instructions[i].opcode),
			result_buf,
			arg1_buf,
			arg2_buf
		);
	}

	fprintf(fp, "-----------------------------------------------------------------------------\n");
}

void binary_free(avm_binary *binary) {
	
	int i;

	if(binary == NULL)
		return;

	for(i = 0; i < binary->string_count; i++)
		free(binary->string_consts[i]);
	free(binary->string_consts);

	free(binary->number_consts);

	for(i = 0; i < binary->userfunc_count; i++)
		free(binary->userfuncs[i].name);
	free(binary->userfuncs);

	for(i = 0; i < binary->libfunc_count; i++)
		free(binary->libfuncs[i]);
	free(binary->libfuncs);

	free(binary->instructions);
	free(binary);
}

static unsigned read_unsigned(FILE *fp) {
	unsigned value;

	assert(fread(&value, sizeof(unsigned), 1, fp) == 1);
	return value;
}

static int read_int(FILE *fp) {
	int value;

	assert(fread(&value, sizeof(int), 1, fp) == 1);
	return value;
}

static double read_double(FILE *fp) {
	double value;

	assert(fread(&value, sizeof(double), 1, fp) == 1);
	return value;
}

static char *read_string(FILE *fp) {
	unsigned length;
	char *str;

	length = read_unsigned(fp);
	str = malloc((length + 1) * sizeof(char));
	assert(str != NULL);

	if(length > 0)
		assert(fread(str, sizeof(char), length, fp) == length);

	str[length] = '\0';
	return str;
}

static void operand_to_text(avm_operand operand, char *buffer, size_t size) {
	switch(operand.type) {
		case label_a:
			snprintf(buffer, size, "label %u", operand.val);
			break;
		case global_a:
			snprintf(buffer, size, "global %u", operand.val);
			break;
		case formal_a:
			snprintf(buffer, size, "formal %u", operand.val);
			break;
		case local_a:
			snprintf(buffer, size, "local %u", operand.val);
			break;
		case number_a:
			snprintf(buffer, size, "number %u", operand.val);
			break;
		case string_a:
			snprintf(buffer, size, "string %u", operand.val);
			break;
		case bool_a:
			snprintf(buffer, size, "bool %u", operand.val);
			break;
		case nil_a:
			snprintf(buffer, size, "nil");
			break;
		case userfunc_a:
			snprintf(buffer, size, "userfunc %u", operand.val);
			break;
		case libfunc_a:
			snprintf(buffer, size, "libfunc %u", operand.val);
			break;
		case retval_a:
			snprintf(buffer, size, "retval");
			break;
		case unused_a:
			snprintf(buffer, size, "-");
			break;
		default:
			snprintf(buffer, size, "?");
			break;
	}
}
