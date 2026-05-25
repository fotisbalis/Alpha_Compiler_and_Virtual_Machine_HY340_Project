#include <assert.h>
#include <stdio.h>

#include "avm_state.h"
#include "binary_loader.h"
#include "execution.h"

static void print_memcell(FILE *fp, const avm_memcell *memcell);
static void print_globals(FILE *fp);

int main(int argc, char **argv) {

	avm_binary *binary;

	assert(argc == 2);

	binary = binary_load_from_path(argv[1]);
	initialize_avm_state(binary);
	execute_cycle();

	fprintf(stdout, "Execution finished.\n");
	print_globals(stdout);

	reset_avm_state();
	free_stack();
	binary_free(binary);

	return 0;
}

static void print_memcell(FILE *fp, const avm_memcell *memcell) {
	assert(fp != NULL);
	assert(memcell != NULL);

	switch(memcell->type) {
		case number_m:
			fprintf(fp, "%f", memcell->data.numVal);
			break;
		case string_m:
			fprintf(fp, "\"%s\"", memcell->data.strVal);
			break;
		case bool_m:
			fprintf(fp, memcell->data.boolVal ? "true" : "false");
			break;
		case userfunc_m:
			fprintf(fp, "userfunc %d", memcell->data.funcVal);
			break;
		case libfunc_m:
			fprintf(fp, "libfunc %s", memcell->data.libfuncVal);
			break;
		case table_m:
			fprintf(fp, "table %p", (void *) memcell->data.tableVal);
			break;
		case nil_m:
			fprintf(fp, "nil");
			break;
		case undef_m:
			fprintf(fp, "undef");
			break;
		default:
			fprintf(fp, "?");
			break;
	}
}

static void print_globals(FILE *fp) {
	int i;
	int stack_index;

	assert(fp != NULL);

	fprintf(fp, "\n--- GLOBALS ---\n");

	for(i = 0; i < get_global_count(); i++) {
		stack_index = (STACK_SIZE - 1) - i;
		assert(stack_index >= 0);
		assert(stack_index < STACK_SIZE);

		fprintf(fp, "global %d = ", i);
		print_memcell(fp, &stack[stack_index]);
		fprintf(fp, "\n");
	}
}
