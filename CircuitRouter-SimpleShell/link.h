#ifndef __LINK_H__
#define __LINK_H__

struct Node {
    process process_r;
    struct Node* next;
};

void push(struct Node** head_ref, process process_n);

void print_it(struct Node* head);

#endif
