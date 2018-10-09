#include <stdio.h>
#include <stdlib.h>
#include "CircuitRouter-SimpleShell.h"
#include "link.h"

void push(struct Node** head_ref, process process_n){ 
    
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
    new_node->process_r  = process_n; 
    new_node->next = (*head_ref); 
    (*head_ref)    = new_node; 
}

void print_it(struct Node* head){ 
    struct Node* current = head;  

    while (current != NULL){ 
        if(current->process_r->status){
            printf("CHILD EXITED (PID=%d; return OK)\n", current->process_r->pid);
        }else{
            printf("CHILD EXITED (PID=%d; return NOK)\n", current->process_r->pid); 
        }
        current = current->next; 
    } 
}
