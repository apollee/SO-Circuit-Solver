#ifndef CIRCUITROUTER_SHELL_H
#define CIRCUITROUTER_SHELL_H

#include "lib/vector.h"
#include <sys/types.h>

typedef struct {
    pid_t pid;
    int status;
    struct timeval start_time;
    double total_time;
} child_t;

void waitForChild();
void printChildren();
child_t* search(int pid);
void create_child(pid_t pid, struct timeval);

#endif /* CIRCUITROUTER_ADVSHELL_H */
