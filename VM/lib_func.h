#ifndef LIBFUNCS_H
#define LIBFUNCS_H

#include "avm_utils.h"

enum library_function_id {
	LIBFUNC_PRINT,
	LIBFUNC_TYPEOF,
	LIBFUNC_TOTALARGUMENTS,
	LIBFUNC_ARGUMENT,
	LIBFUNC_UNSUPPORTED
};

void call_library_function(const char *name);

void libfunc_print();
void libfunc_typeof();
void libfunc_totalarguments();
void libfunc_argument();

#endif
