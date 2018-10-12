#include <stdio.h>
#include <stdlib.h>
#include "CircuitRouter-SimpleShell.h"
#include "link.h"


/* =============================================================================
 * push
 * receives the head of the list and inserts a process
 * =============================================================================
 */
void push(struct Node** head_ref, process process_n){ 
    
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
    new_node->process_r  = process_n; 
    new_node->next = (*head_ref); 
    (*head_ref)    = new_node; 
}

/* =============================================================================
 * print_it
 * receives the head of the list and prints the pid and status of the child 
 * processes
 * =============================================================================
 */
void print_it(struct Node* head){ 
    struct Node* current = head;  

    while (current != NULL){ 
        if(!(current->process_r->status)){
            printf("CHILD EXITED (PID=%d; return OK)\n", current->process_r->pid);
        }else{
            printf("CHILD EXITED (PID=%d; return NOK)\n", current->process_r->pid); 
        }
        current = current->next; 
    } 
}


/* =============================================================================
 * delete_it
 * receives the head of the list and deletes the list while freeing memory
 * =============================================================================
 */
void delete_it(struct Node** head){ 
   struct Node* current = *head; 
   struct Node* next; 
  
   while (current != NULL){ 
       next = current->next;
       free(current->process_r);
       free(current); 
       current = next; 
   } 
    
   *head = NULL; 
} 

