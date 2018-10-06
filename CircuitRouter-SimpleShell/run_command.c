#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "run_command.h"
#include "../lib/list.h"


/*function that starts a process*/
int start_process(int max_children, char* file_name, list_t* list_pids, int counter){
    pid_t pid;

    if((max_children < counter) && (max_children != -1)){
	int status;
	pid_t pid_ter = wait(&status);
        int status_proc = WIFEXITED(status);
        printf("status_proc: %d\n", status_proc);
        printf("status: %d\n", status);
        printf("pid_ter: %d\n", pid_ter); 
        
        process_t new_proc = malloc(sizeof(struct process));
        new_proc->pid = pid_ter;
        new_proc->status = status_proc;
        list_insert(list_pids, new_proc);
        counter--;
    }
    
    pid = fork();
    if(pid == 0){
        child_process(max_children, file_name, list_pids, counter);
    }
    else if(pid < 0){ 
        printf("Error creating a process.\n");
        exit(-1);
    }
    else{ 
    }
    return 0;
}


void child_process(int max_children, char* file_name, list_t* list_pids, int counter){

    if((max_children >= counter) || (max_children == -1)){
        printf("the number of max_children is: %d\n", max_children);
        printf("the counter is: %d\n", counter);
        execl(PATH_SEQSOLVER, SEQ_SOLVER_EX, file_name, (char *)0);
          
    }
}



/*
void exit_shell(list_t* list_pids){

    percorrer lista{
        
        waitpid(list_pids->pid, &status, 0);
        list_pids->status = status;
}
*/


 




