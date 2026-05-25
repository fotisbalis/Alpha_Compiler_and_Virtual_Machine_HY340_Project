#ifndef INCOMPLETE_JUMPS_H
#define INCOMPLETE_JUMPS_H

typedef struct IncompleteJump {
	int instrNo;
	int iaddress;
} IncompleteJump;

void add_incomplete_jump(int instrNo, int iaddress);

void expand_incomplete_jumps();

IncompleteJump *get_incomplete_jumps();

int get_incomplete_jump_count();

void patch_incomplete_jumps();

void free_incomplete_jumps();

#endif
