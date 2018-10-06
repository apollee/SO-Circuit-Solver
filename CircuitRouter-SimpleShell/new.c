#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "commandlinereader.h"

#define MAXARGS 5
#define BUFFERSIZE 500

#define COMMAND_RUN "run"
#define COMMAND_EXIT "exit"
#define ERROR_COMMAND "Invalid syntax, try again."
#define PATH_SEQSOLVER "../CircuitRouter-SeqSolver/CircuitRouter-SeqSolver"
#define SEQ_SOLVER_EX "CircuitRouter-SeqSolver"

typedef struct process{
    pid_t pid;
	int status;
}*process;

struct Node { 
    process process_r; 
    struct Node* next; 
}; 

int counter = 0;


void push(struct Node** head_ref, process process_n){ 
    /* allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
  
    /* put in the key  */
    new_node->process_r  = process_n; 
  
    /* link the old list off the new node */
    new_node->next = (*head_ref); 
  
    /* move the head to point to the new node */
    (*head_ref)    = new_node; 
}

void print_it(struct Node* head){ 
    struct Node* current = head;  // Initialize current 
    while (current != NULL){ 
        if(current->process_r->status){
            printf("CHILD EXITED (PID: %d; return OK)\n", current->process_r->pid);
        }else{
            printf("CHILD EXITED (PID: %d; return NOK)\n", current->process_r->pid); 
        }
        current = current->next; 
    } 
}  

int main(int argc, char ** argv){
    int max_children = -1;
    struct Node* head = NULL;
    pid_t pid; 

    if(argc == 2){
        max_children = atoi(argv[1]);
    }


    while(1){
        char *args[MAXARGS + 1];
        char buffer[BUFFERSIZE];

        int number_args = readLineArguments(args, MAXARGS + 1, buffer, BUFFERSIZE);

        if(number_args == 0){
            continue;
        }

        /*command exit*/
        if(strcmp(args[0], COMMAND_EXIT) == 0){
            if(number_args >= 2){
                printf("%s\n", ERROR_COMMAND);
                continue;
            }
            /*waiting for processes and exiting*/
            if(max_children != -1){
                print_it(head);
            }
 
            int i, status; 
            for(i = 0; i < counter; i++){
                pid_t pid_f = wait(&status);
                int status_proc = WIFEXITED(status);
                if(status_proc){
                    printf("CHILD EXITED, PID: %d; return: OK)\n", pid_f);
                }else{
                    printf("CHILD EXITED, PID: %d; return NOK)\n", pid_f);    
                }
            }

        }


        /*command run*/
        else if(strcmp(args[0], COMMAND_RUN) == 0){
            if(number_args < 2 || number_args >= 3){
                 printf("%s\n", ERROR_COMMAND);
                continue;
            }

            if(access(args[1], R_OK) == -1){
                printf("File doesnt exist, try again.\n");
                continue;
            }
            
            /*executing the file_name and starting the process*/
            if((max_children < counter) && (max_children != -1)){
                int status;
                pid_t pid_ter = wait(&status);
                int status_proc = WIFEXITED(status);
                printf("pid: %d\n", pid_ter);
                process new_proc = malloc(sizeof(struct process));
                new_proc->pid = pid_ter;
                new_proc->status = status_proc;    
                push(&head, new_proc);
                counter--;
            }
            
            pid = fork();
            if(pid == 0){
                execl(PATH_SEQSOLVER, SEQ_SOLVER_EX, args[1], (char *)0);
            }else if(pid < 0){
                printf("Error creating a process.\n");
            }else{
               counter++; 
            }
                
        }

        else{
            printf("Invalid syntax or unknown command, try again.\n");  
        }
    }
    return 0;
}


