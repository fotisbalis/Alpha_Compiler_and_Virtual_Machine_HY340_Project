#ifndef CALLSUFFIX_H
#define CALLSUFFIX_H

#include "expr.h"

typedef struct CallSuffix {
	ExprList *params;
	int is_method;
	char *method_name;
} CallSuffix;

#endif
