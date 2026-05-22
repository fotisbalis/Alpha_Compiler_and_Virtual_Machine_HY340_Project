#ifndef CONST_TABLES_H
#define CONST_TABLES_H

#include "instructions.h"

int new_const_string(char *str);
char **get_string_consts();
int get_string_count();

int new_const_number(double num);
double *get_number_consts();
int get_number_count();

int new_const_libfunc(char *name);
char **get_libfunc_consts();
int get_libfunc_count();

int new_const_userfunc(int address, int localSize, char *name);
void update_const_userfunc(int address, int localSize, char *name);
UserFunc *get_userfunc_consts();
int get_userfunc_count();

void free_const_tables();

#endif
