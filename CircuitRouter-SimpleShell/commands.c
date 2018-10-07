#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "linked_l.h"
#include "circuit.h"
#include "commands.h"

void exit_shell(int max_children, struct Node* head, int counter){
    int i, status;

    if(max_children != -1){
        print_it(head);
    }

    for(i = 0; i < counter; i++){
        pid_t pid_f = wait(&status);
        int status_proc = WIFEXITED(status);
        if(status_proc){
            printf("CHILD EXITED, (PID %d; return: OK)\n", pid_f);
        }else{
            printf("CHILD EXITED, (PID: %d; return NOK)\n", pid_f);
        }
    }
    printf("END.\n");
    exit(0);
}


void run(struct Node* head, int counter, int max_children, char* file_name){
    
    pid_t pid;

    if((max_children < counter) && (max_children != -1)){
        int status, status_proc;
        pid_t pid_ter = wait(&status);
        status_proc = WIFEXITED(status);
        
        process finished_proc = malloc(sizeof(struct process));
        finished_proc->pid = pid_ter;
        finished_proc->status = status_proc;
        push(&head, finished_proc);
        counter--;
    }

    pid = fork();
        
    if(pid == 0){
        execl(PATH_SEQSOLVER, SEQ_SOLVER_EX, file_name, (char *)0);
    }
    else if(pid < 0){
        printf("Error creating a process.\n");
    }
    else{
    }
}
