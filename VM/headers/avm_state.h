#ifndef AVM_STATE_H
#define AVM_STATE_H

#include "avm_types.h"
#include "memcell.h"

#define STACKENV_SIZE 4
#define NUMACTUALS_OFFSET 4
#define SAVEDPC_OFFSET 3
#define SAVEDTOP_OFFSET 2
#define SAVEDTOPSP_OFFSET 1

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
int get_global_topsp();

/* boolean */
int get_execution_finished();
void set_execution_finished(int finished);

int get_total_actuals();
void inc_total_actuals();
void reset_total_actuals();

void push_env_value(int value);
int get_env_value(int current_topsp, int offset);
void save_call_environment();

avm_memcell *get_retval_register();
avm_memcell *get_ax_register();
avm_memcell *get_bx_register();
avm_memcell *get_cx_register();

#endif
