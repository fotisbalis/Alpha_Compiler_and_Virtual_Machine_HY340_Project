#ifndef GENERATOR_H
#define GENERATOR_H

#include "quad.h"
#include "instructions.h"

typedef void (*generator_func_t)(Quad *quad);

void reset_operand(ioperand *operand);
void make_operand(Expr *expr, ioperand *operand);
void make_bool_operand(ioperand *operand, int value);
void make_retval_operand(ioperand *operand);
void make_var_operand(Symbol *sym, ioperand *operand);

void generate(iopcode op, Quad *quad);

void generate_relational(iopcode op, Quad *quad);

void generate_ASSIGN(Quad *quad);
void generate_ADD(Quad *quad);
void generate_SUB(Quad *quad);
void generate_MUL(Quad *quad);
void generate_DIV(Quad *quad);
void generate_MOD(Quad *quad);
void generate_UMINUS(Quad *quad);

void generate_NEWTABLE(Quad *quad);
void generate_TABLEGETELEM(Quad *quad);
void generate_TABLESETELEM(Quad *quad);

void generate_JUMP(Quad *quad);
void generate_IF_EQ(Quad *quad);
void generate_IF_NOTEQ(Quad *quad);
void generate_IF_GREATER(Quad *quad);
void generate_IF_GREATEREQ(Quad *quad);
void generate_IF_LESS(Quad *quad);
void generate_IF_LESSEQ(Quad *quad);

void generate_NOT(Quad *quad);
void generate_OR(Quad *quad);
void generate_AND(Quad *quad);

void generate_PARAM(Quad *quad);
void generate_CALL(Quad *quad);
void generate_GETRETVAL(Quad *quad);

void generate_FUNCSTART(Quad *quad);
void generate_RETURN(Quad *quad);
void generate_FUNCEND(Quad *quad);

void generate_NOP();

void generate_instruction_for_quad(Quad *quad);
void generate_all_instructions();

#endif
