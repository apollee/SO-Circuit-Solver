#ifndef __COMMANDS__
#define __COMMANDS__

#define PATH_SEQSOLVER "../CircuitRouter-SeqSolver/CircuitRouter-SeqSolver"
#define SEQ_SOLVER_EX "CircuitRouter-SeqSolver"
#include "linked_l.h"

void exit_shell(int max_children, struct Node* head, int counter);

void run(struct Node* head, int counter, int max_children, char* file_name);

#endif
