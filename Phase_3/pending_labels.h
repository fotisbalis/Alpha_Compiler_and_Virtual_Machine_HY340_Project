#ifndef PENDING_LABELS_H
#define PENDING_LABELS_H

/* Stores the quads where there are jumps or branches with no label yet */
typedef struct PendingLabel {
        int quadID;
        struct PendingLabel *next;
} PendingLabel;

PendingLabel* create_pending_label(int quadID);

void fill_pending_labels_of_list(PendingLabel *list, int label);

PendingLabel* merge_jump_lists(PendingLabel *l1, PendingLabel *l2);

#endif
