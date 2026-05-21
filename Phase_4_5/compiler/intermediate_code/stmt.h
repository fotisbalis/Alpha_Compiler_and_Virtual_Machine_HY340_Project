#ifndef STMT_H
#define STMT_H

#include "pending_labels.h"

/* Stores pending labels of a statement */
typedef struct Stmt {
        PendingLabel *BreakLabels;
        PendingLabel *ContinueLabels;
} Stmt;

Stmt* create_stmt();

#endif
