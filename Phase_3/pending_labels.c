#include <stdio.h>
#include <stdlib.h>

#include "pending_labels.h"
#include "quad.h"

PendingLabel* create_pending_label(int quadID){
 
     	PendingLabel *pl = malloc(sizeof(PendingLabel));

    	pl->quadID = quadID;
    	pl->next = NULL;

    	return pl;
}

void fill_pending_labels_of_list(PendingLabel *list, int label){
	
	PendingLabel *tmp = list;

    	while(tmp != NULL){
        	fill_pending_label(tmp->quadID, label);
        	tmp = tmp->next;
    	}
}

PendingLabel* merge_pending_labels(PendingLabel *l1, PendingLabel *l2){

	PendingLabel *tmp;

	if(l1 == NULL) return l2;

	tmp = l1;
	while(tmp != NULL) tmp = tmp->next;

	tmp->next = l2;

	return l1;
}
