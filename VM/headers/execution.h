#ifndef EXECUTION_H
#define EXECUTION_H

#include "avm_utils.h"
#include "lib_func.h"
#include "table.h"

typedef void (*execute_func_t)(const avm_instruction *instruction);

void execute_current_instruction(avm_binary *binary);

void execute_assign(const avm_instruction *instruction);
void execute_add(const avm_instruction *instruction);
void execute_sub(const avm_instruction *instruction);
void execute_mul(const avm_instruction *instruction);
void execute_div(const avm_instruction *instruction);
void execute_mod(const avm_instruction *instruction);

void execute_jeq(const avm_instruction *instruction);
void execute_jne(const avm_instruction *instruction);
void execute_jle(const avm_instruction *instruction);
void execute_jge(const avm_instruction *instruction);
void execute_jlt(const avm_instruction *instruction);
void execute_jgt(const avm_instruction *instruction);
void execute_jump(const avm_instruction *instruction);

void execute_call(const avm_instruction *instruction);
void execute_pusharg(const avm_instruction *instruction);
void execute_funcstart(const avm_instruction *instruction);
void execute_funcend(const avm_instruction *instruction);

void execute_newtable(const avm_instruction *instruction);
void execute_tablesetelem(const avm_instruction *instruction);
void execute_tablegetelem(const avm_instruction *instruction);

void execute_nop(const avm_instruction *instruction);

void execute_unsupported(const avm_instruction *instruction);

#endif
