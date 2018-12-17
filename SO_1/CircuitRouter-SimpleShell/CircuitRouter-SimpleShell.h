#ifndef __NEW_H__
#define __NEW_H__

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


#endif
