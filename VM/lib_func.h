#ifndef LIBFUNCS_H
#define LIBFUNCS_H

#include "avm_utils.h"
#include "table.h"

enum library_function_id {
	LIBFUNC_PRINT,
	LIBFUNC_PRINTLN,
	LIBFUNC_TYPEOF,
	LIBFUNC_TOTALARGUMENTS,
	LIBFUNC_ARGUMENT,
	LIBFUNC_STRTONUM,
	LIBFUNC_SQRT,
	LIBFUNC_COS,
	LIBFUNC_SIN,
	LIBFUNC_UNSUPPORTED
};

void call_library_function(const char *name);

void libfunc_print();
void libfunc_println();
void libfunc_typeof();
void libfunc_totalarguments();
void libfunc_argument();
void libfunc_strtonum();
void libfunc_sqrt();
void libfunc_cos();
void libfunc_sin();

#endif
