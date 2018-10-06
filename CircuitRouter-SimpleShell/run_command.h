#ifndef __RUNCOMMAND__
#define __RUNCOMMAND__

#define PATH_SEQSOLVER "../CircuitRouter-SeqSolver/CircuitRouter-SeqSolver"
#define SEQ_SOLVER_EX "CircuitRouter-SeqSolver"

#include "../lib/list.h"
#include <unistd.h>
#include <sys/types.h>

typedef struct process{
    int pid;
    int status;
}*process_t;


int start_process(int max_children, char* file_name, list_t* list_pids, int counter);

void child_process(int max_children, char* file_name, list_t* list_pids, int counter);


#endif 
