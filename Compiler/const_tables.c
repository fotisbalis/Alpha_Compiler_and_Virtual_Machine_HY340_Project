#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "const_tables.h"

static char **string_consts = NULL;
static int string_count = 0;
static int string_capacity = 0;

static double *number_consts = NULL;
static int number_count = 0;
static int number_capacity = 0;

static char **libfunc_consts = NULL;
static int libfunc_count = 0;
static int libfunc_capacity = 0;

static UserFunc *userfunc_consts = NULL;
static int userfunc_count = 0;
static int userfunc_capacity = 0;

static void *expand_array(void *array, int *capacity, size_t element_size);

int new_const_string(char *str) {
	
	int i;
	char *copy;

	assert(str != NULL);

	for(i = 0; i < string_count; i++) {
		if(strcmp(string_consts[i], str) == 0)
			return i;
	}

	if(string_count >= string_capacity)
		string_consts = expand_array(string_consts, &string_capacity, sizeof(char *));

	copy = strdup(str);
	assert(copy != NULL);

	string_consts[string_count] = copy;
	return string_count++;
}

char **get_string_consts() {
	return string_consts;
}

int get_string_count() {
	return string_count;
}

int new_const_number(double num) {
	
	int i;

	for(i = 0; i < number_count; i++) {
		if(number_consts[i] == num)
			return i;
	}

	if(number_count >= number_capacity)
		number_consts = expand_array(number_consts, &number_capacity, sizeof(double));

	number_consts[number_count] = num;
	return number_count++;
}

double *get_number_consts() {
	return number_consts;
}

int get_number_count() {
	return number_count;
}

int new_const_libfunc(char *name) {
	
	int i;
	char *copy;

	assert(name != NULL);

	for(i = 0; i < libfunc_count; i++) {
		if(strcmp(libfunc_consts[i], name) == 0)
			return i;
	}

	if(libfunc_count >= libfunc_capacity)
		libfunc_consts = expand_array(libfunc_consts, &libfunc_capacity, sizeof(char *));

	copy = strdup(name);
	assert(copy != NULL);

	libfunc_consts[libfunc_count] = copy;
	return libfunc_count++;
}

char **get_libfunc_consts() {
	return libfunc_consts;
}

int get_libfunc_count() {
	return libfunc_count;
}

int new_const_userfunc(int address, int localSize, char *name) {
	
	int i;
	char *copy;

	assert(address >= -1);
	assert(localSize >= -1);
	assert(name != NULL);

	for(i = 0; i < userfunc_count; i++) {
		if(strcmp(userfunc_consts[i].name, name) == 0) {
			if(address != -1)
				userfunc_consts[i].address = address;
			if(localSize != -1)
				userfunc_consts[i].localSize = localSize;

			return i;
		}
	}

	if(userfunc_count >= userfunc_capacity)
		userfunc_consts = expand_array(userfunc_consts, &userfunc_capacity, sizeof(UserFunc));

	copy = strdup(name);
	assert(copy != NULL);

	userfunc_consts[userfunc_count].address = address;
	userfunc_consts[userfunc_count].localSize = localSize;
	userfunc_consts[userfunc_count].name = copy;

	return userfunc_count++;
}

void update_const_userfunc(int address, int localSize, char *name) {
	int i;

	assert(address >= -1);
	assert(localSize >= -1);
	assert(name != NULL);

	for(i = 0; i < userfunc_count; i++) {
		if(strcmp(userfunc_consts[i].name, name) == 0) {
			if(address != -1)
				userfunc_consts[i].address = address;
			if(localSize != -1)
				userfunc_consts[i].localSize = localSize;
			return;
		}
	}

	new_const_userfunc(address, localSize, name);
}

UserFunc *get_userfunc_consts() {
	return userfunc_consts;
}

int get_userfunc_count() {
	return userfunc_count;
}

void free_const_tables() {
	
	int i;

	for(i = 0; i < string_count; i++) free(string_consts[i]);
	free(string_consts);
	string_consts = NULL;
	string_count = 0;
	string_capacity = 0;

	free(number_consts);
	number_consts = NULL;
	number_count = 0;
	number_capacity = 0;

	for(i = 0; i < libfunc_count; i++) free(libfunc_consts[i]);
	free(libfunc_consts);
	libfunc_consts = NULL;
	libfunc_count = 0;
	libfunc_capacity = 0;

	for(i = 0; i < userfunc_count; i++) free(userfunc_consts[i].name);
	free(userfunc_consts);
	userfunc_consts = NULL;
	userfunc_count = 0;
	userfunc_capacity = 0;
}

static void *expand_array(void *array, int *capacity, size_t element_size) {

	void *expanded_array;

	assert(capacity != NULL);
	assert(element_size > 0);

	*capacity += 128;
	expanded_array = realloc(array, (*capacity) * element_size);
	assert(expanded_array != NULL);

	return expanded_array;
}
