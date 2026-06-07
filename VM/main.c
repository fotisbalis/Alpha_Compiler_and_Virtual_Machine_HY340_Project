#include <assert.h>
#include <stdio.h>

#include "headers/avm_state.h"
#include "headers/binary_loader.h"
#include "headers/execution.h"

int main(int argc, char **argv) {

	avm_binary *binary;

	assert(argc == 2);

	binary = binary_load_from_path(argv[1]);
	
	initialize_avm_state(binary);

	while(!get_execution_finished()) {
		if(get_pc() >= 0 && get_pc() < binary->instruction_count)
			execute_current_instruction(binary);
		else
                        set_execution_finished(True);
        }

	reset_avm_state();
	free_stack();
	binary_free(binary);

	return 0;
}
