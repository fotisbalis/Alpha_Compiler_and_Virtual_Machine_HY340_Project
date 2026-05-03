#ifndef STMT_H
#define STMT_H

#include "pending_labels.h"

/* Stores pending labels of a statement */
typedef struct Stmt {
        PendingLabel *JumpLabels; /* jump to next part of the statement */
        PendingLabel *BreakLabels;
        PendingLabel *ContinueLabels;
} Stmt;

Stmt* create_stmt();

#endif
