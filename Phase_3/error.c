#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"

Error* head = NULL;
Error* tail = NULL;

int count = 0;

void add_new_error(char* error_message){
	
	Error* err = malloc(sizeof(Error));

	err->message = strdup(error_message);
	err->next = NULL;

	if(head == NULL){
		head = err;
		tail = err;
	}
	else{
		tail->next = err;
		tail = err;
	}

	count++;
}

int has_errors(){

	if(head == NULL)
		return 0;

	return 1;
}

int error_count(){

        return count;
}

void print_errors(){

	Error* err;

	printf("\n--------- Errors ---------\n");

	for(err = head; err != NULL; err = err->next)
		printf("%s\n", err->message);
}

void free_errors(){
	
	Error* err = head;

	while(err != NULL){
		Error* tmp = err;
		err = err->next;
		
		free(tmp->message);
		free(tmp);
	}
}
