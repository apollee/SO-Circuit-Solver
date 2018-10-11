#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "commandlinereader.h"
#include "CircuitRouter-SimpleShell.h"
#include "link.h"

int counter = 0;

int main(int argc, char ** argv){
    int max_children = -1;
    struct Node* head = NULL;
    pid_t pid; 

    if(argc == 2){ //if the user inserted a max_children parameter
        max_children = atoi(argv[1]);
    }


    while(1){
        char *args[MAXARGS + 1];
        char buffer[BUFFERSIZE];
        int i, status;
        int number_args = readLineArguments(args, MAXARGS + 1, buffer, BUFFERSIZE);

        if(number_args == 0){
            continue;
        }

        /*command exit*/
        else if(strcmp(args[0], COMMAND_EXIT) == 0){
            if(number_args >= 2){
                printf("%s\n", ERROR_COMMAND);
                continue;
            }
            if(max_children != -1){ //max_children defined
                print_it(head); //list with dead processes
                delete_it(&head);
            }
 
            for(i = 0; i < counter; i++){ //waiting for processes to end
                pid_t pid_f = wait(&status);
                int status_proc = WIFEXITED(status);
                if(status_proc){
                    printf("CHILD EXITED (PID=%d; return OK)\n", pid_f);
                }else{
                    printf("CHILD EXITED (PID=%d; return NOK)\n", pid_f);    
                }
            }

        printf("END.\n");     
        exit(0);
        }


        /*command run*/
        else if(strcmp(args[0], COMMAND_RUN) == 0){
            int status;
            counter++;
 
            if(number_args < 2 || number_args >= 3){
                 printf("%s\n", ERROR_COMMAND);
                continue;
            }
        
            /*if max_children is defined and == counter of current processes*/
            if((max_children < counter) && (max_children != -1)){ 
                pid_t pid_ter = wait(&status);
                int status_proc = WIFEXITED(status);
                
                process new_proc = malloc(sizeof(struct process));
                new_proc->pid = pid_ter;
                new_proc->status = status_proc;    
                push(&head, new_proc); //save in linked list of dead processes
                counter--;
            }
            
            pid = fork();
            if(pid == 0){
                execl(PATH_SEQSOLVER, SEQ_SOLVER_EX, args[1], (char *)0);
            }
            else if(pid < 0){
                printf("Error creating a process.\n");
            }
                
        }

        else{
            printf("Invalid syntax or unknown command, try again.\n");  
        }
    }

    return 0;
}
