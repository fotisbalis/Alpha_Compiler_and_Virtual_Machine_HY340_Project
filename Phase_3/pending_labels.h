#ifndef PENDING_LABELS_H
#define PENDING_LABELS_H

/* Stores the quads where there are jumps or branches with no label yet */
typedef struct PendingLabel {
        int quadID;
        struct PendingLabel *next;
} PendingLabel;

/* Stores pending labels of a statement */
typedef struct Stmt {
        PendingLabel *JumpLabels; /* jump to next part of the statement */
        PendingLabel *BreakLabels;
        PendingLabel *ContinueLabels;
} Stmt;

#endif
