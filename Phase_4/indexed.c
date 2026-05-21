#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "indexed.h"

Indexed* create_indexed(Expr *index, Expr *val){

	Indexed *ind = malloc(sizeof(Indexed));

	ind->index = index;
	ind->val = val;

	return ind;
}

IndexedList* create_indexed_list(){

	IndexedList *list = malloc(sizeof(IndexedList));

        list->head = NULL;
        list->tail = NULL;

        return list;
}

void add_indexed(IndexedList *list, Indexed *ind){

	assert(list != NULL && ind != NULL && ind->next == NULL);

        if(list->head == NULL){
                list->head = ind;
                list->tail = ind;
        }
        else{
                list->tail->next = ind;
                list->tail = ind;
        }
}
