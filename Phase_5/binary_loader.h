#ifndef BINARY_LOADER_H
#define BINARY_LOADER_H

#include <stdio.h>

#include "avm_types.h"

#define AVM_BINARY_MAGIC 34020026u

const char *avm_opcode_to_string(int opcode);

const char *avm_operand_type_to_string(int type);

avm_binary *binary_load(FILE *fp);

avm_binary *binary_load_from_path(const char *path);

void binary_print(FILE *fp, const avm_binary *binary);

void binary_free(avm_binary *binary);

#endif
