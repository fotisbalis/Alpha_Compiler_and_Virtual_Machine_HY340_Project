#ifndef UTILS_H
#define UTILS_H

#include "symbol.h"
#include "symbol_table.h"
#include "expr.h"
#include "quad.h"

/* prints a grammar reduce */
void print_reduce(char *left, char* right);

/* checks if a symbol name matches the name of a library function */
Symbol* check_for_lib_func(SymTable_T oSymTable, char *name);

/* creates a temporary symbol in the symTable */
Symbol* new_tmp(SymTable_T oSymTable, int scope, int line);

/* handles if_greater, if_greater_equal, if_less... quads */
Expr* handle_comparison_quad(opcode op, Expr *arg1, Expr *arg2, SymTable_T sym_table, int current_scope, int line);

#endif
