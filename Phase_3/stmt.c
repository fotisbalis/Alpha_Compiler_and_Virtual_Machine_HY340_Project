#include <stdio.h>
#include <stdlib.h>

#include "stmt.h"

Stmt* create_stmt(void){

	Stmt *stmt = malloc(sizeof(Stmt));

	stmt->JumpLabels = NULL;
    	stmt->BreakLabels = NULL;
    	stmt->ContinueLabels = NULL;
	
	return stmt;
}
