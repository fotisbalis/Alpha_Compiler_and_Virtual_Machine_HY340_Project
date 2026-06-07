#include <assert.h>
#include <stdlib.h>

#include "headers/incomplete_jumps.h"
#include "headers/instructions.h"
#include "headers/quad.h"

#define EXPAND_SIZE 128

static int count = 0;
static int capacity = 0;
static IncompleteJump *incomplete_jumps = NULL;

void add_incomplete_jump(int instrNo, int iaddress) {
	assert(instrNo >= 0);
	assert(iaddress >= 0);

	if(count >= capacity)
		expand_incomplete_jumps();

	incomplete_jumps[count].instrNo = instrNo;
	incomplete_jumps[count].iaddress = iaddress;
	count++;
}

void expand_incomplete_jumps() {
	IncompleteJump *tmp;

	capacity += EXPAND_SIZE;
	tmp = realloc(incomplete_jumps, capacity * sizeof(IncompleteJump));
	assert(tmp != NULL);

	incomplete_jumps = tmp;
}

IncompleteJump *get_incomplete_jumps() {
	return incomplete_jumps;
}

int get_incomplete_jump_count() {
	return count;
}

void patch_incomplete_jumps() {
	
	int i;
	Quad *quads = get_quads();
	Instruction *instructions = get_instructions();
	int quad_count = get_quad_count();
	int instruction_count = get_instruction_count();

	for(i = 0; i < count; i++) {
		int instrNo = incomplete_jumps[i].instrNo;
		int iaddress = incomplete_jumps[i].iaddress;

		assert(instrNo >= 0 && instrNo < instruction_count);
		assert(iaddress >= 0 && iaddress <= quad_count);

		if(iaddress == quad_count)
			instructions[instrNo].result.val = instruction_count;
		else {
			assert(quads[iaddress].taddress >= 0);
			instructions[instrNo].result.val = quads[iaddress].taddress;
		}
	}
}

void free_incomplete_jumps() {
	free(incomplete_jumps);
	incomplete_jumps = NULL;
	count = 0;
	capacity = 0;
}
