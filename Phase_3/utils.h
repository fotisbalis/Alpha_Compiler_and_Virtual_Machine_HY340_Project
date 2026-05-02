#ifndef UTILS_H
#define UTILS_H

#include "symbol.h"
#include "symbol_table.h"

/* prints a grammar reduce */
void print_reduce(char *left, char* right);

/* checks if a symbol name matches the name of a library function */
Symbol* check_for_lib_func(SymTable_T oSymTable, char *name);

/* creates a temporary symbol in the symTable */
Symbol* new_tmp(SymTable_T oSymTable, int scope, int line);

#endif
