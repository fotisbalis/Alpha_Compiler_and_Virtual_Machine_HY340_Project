#ifndef AVM_UTILS_H
#define AVM_UTILS_H

#include "avm_state.h"
#include "table.h"

#define STACKENV_SIZE 4

avm_memcell *translate_operand(const avm_operand *operand, avm_memcell *reg);

void runtime_error(const char *message);

void runtime_warning(const char *message);

int get_current_total_actuals();

avm_memcell *get_actual(int index);

int get_caller_topsp();

void set_retval_nil();

void restore_after_libfunc_call();

void set_retval_table(avm_table *table);

void set_number_memcell(avm_memcell *memcell, double value);

void set_string_memcell(avm_memcell *memcell, const char *value);

#endif
