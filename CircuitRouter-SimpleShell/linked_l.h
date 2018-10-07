#ifndef __LINKED_L__
#define __LINKED_L__

#include "circuit.h"

struct Node {
    process process_r;
    struct Node* next;
};

void push(struct Node** head_ref, process process_n);

void print_it(struct Node* head);

#endif
