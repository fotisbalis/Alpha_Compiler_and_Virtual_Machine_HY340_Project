#ifndef UTILS_H
#define UTILS_H

#include "symbol.h"
#include "symbol_table.h"
#include "expr.h"
#include "indexed.h"
#include "quad.h"

/* prints a grammar reduce */
void print_reduce(char *left, char* right);

/* checks if a symbol name matches the name of a library function */
Symbol* check_for_lib_func(SymTable_T oSymTable, char *name);

/* creates a temporary symbol in the symTable */
Symbol* new_tmp(SymTable_T oSymTable, int scope, int line);

/* handles if_greater, if_greater_equal, if_less... quads */
Expr* handle_comparison_quad(opcode op, Expr *arg1, Expr *arg2, SymTable_T sym_table, int current_scope, int line);

/* creates quads from an elist of params from left to right */
void handle_param_quads(ExprList *params);

Expr* make_call(Expr *func, ExprList *elist, SymTable_T sym_table, int current_scope, int line);

Expr* create_member(Expr *table, char *name, Expr *index);

Expr* get_table(Expr *expr, SymTable_T sym_table, int current_scope, int line);

Expr* create_table(SymTable_T sym_table, int current_scope, int line);

void add_elist_to_table(ExprList *elist, Expr *table);

void add_indexed_to_table(IndexedList *list, Expr *table);

Expr* handle_pre_inc_dec(Expr *lvalue, opcode op, SymTable_T sym_table, int current_scope, int line);

Expr* handle_post_inc_dec(Expr *lvalue, opcode op, SymTable_T sym_table, int current_scope, int line);

#endif
