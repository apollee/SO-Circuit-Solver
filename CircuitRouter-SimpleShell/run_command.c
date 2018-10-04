#include <stdio.h>
#include <stdlib.h>
#include "runcommmand.h"

int counter = 0;

/*function that starts a process*/
int start_process(int max_children, char* file_name, list_t* list_pids){
    int pid;
    
    pid = fork();
    if(pid == 0){
        child_process();
    }
    else if(pid < 0){ 
        printf("Error creating a process.\n");
        exit(-1);
    }
    else{
        parent_process(max_children, pid, list_t* list_pids);
    }
}


void child_process(int max_children){
    if(max_children != counter){
        execl("../CircuitRouter-SeqSolver/CircuitRouter-SeqSolver", "CircuitRouter-SeqSolver", file_name, 0);
        counter++;
    else{
        wait()       
    exit(-1);
}


void parent_process(int max_children, int pid, list_t* list_pids){
    process_t new_proc = malloc(sizeof(struct process));
    new_proc->pid = pid;
    list_insert(list_pids, new_proc);
    counter++; 
}






 





