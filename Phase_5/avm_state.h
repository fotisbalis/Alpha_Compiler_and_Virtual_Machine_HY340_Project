#ifndef AVM_STATE_H
#define AVM_STATE_H

#include "avm_types.h"
#include "memcell.h"

void initialize_avm_state(avm_binary *binary);

void reset_avm_state();

int get_global_count();

void reset_register(avm_memcell *memcell);

avm_binary *get_program_binary();

int get_pc();
void set_pc(int new_pc);

int get_top();
void set_top(int new_top);

int get_topsp();
void set_topsp(int new_topsp);

/* boolean */
int get_execution_finished();
void set_execution_finished(int finished);

avm_memcell *get_retval_register();
avm_memcell *get_ax_register();
avm_memcell *get_bx_register();
avm_memcell *get_cx_register();

#endif
