#include <assert.h>
#include <stdio.h>

#include "binary_loader.h"

int main(int argc, char **argv) {

	avm_binary *binary;

	assert(argc == 2);

	binary = binary_load_from_path(argv[1]);
	binary_print(stdout, binary);
	binary_free(binary);

	return 0;
}
