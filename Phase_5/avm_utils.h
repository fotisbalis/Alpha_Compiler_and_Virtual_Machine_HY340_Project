#ifndef AVM_UTILS_H
#define AVM_UTILS_H

#include "avm_state.h"

#define STACKENV_SIZE 4

avm_memcell *translate_operand(const avm_operand *operand, avm_memcell *reg);

#endif
