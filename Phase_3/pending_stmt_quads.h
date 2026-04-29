#ifndef PENDING_STMT_QUADS_H
#define PENDING_STMT_QUADS_H

/* Stores the quads where there are jumps or branches with no known destination yet */
typedef struct PendingQuads {
        int quad;
        struct PendingQuads *next;
} PendingQuads;

/* Stores pending quads of a statement */
typedef struct Stmt_PendingQuads {
        PendingQuads *JumpQuads; /* jump to next part of the statement */
        PendingQuads *BreakQuads;
        PendingQuads *ContinueQuads;
} Stmt_PendingQuads;

#endif
