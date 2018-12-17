
/*
// Projeto SO - exercise 3
// Sistemas Operativos, Pedro Lamego, Maria Beatriz Martins 2018-19
*/

#include "lib/commandlinereader.h"
#include "lib/vector.h"
#include "lib/timer.h"
#include "../lib/library.h"
#include "CircuitRouter-AdvShell.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>

#define COMMAND_EXIT "exit"
#define COMMAND_RUN "run"

#define MAXARGS 30
#define BUFFER_SIZE 100

vector_t *children;


void waitForChild() {
    while (1) {
        int pid, status;
        pid = wait(&status);
        child_t* child;
        if(pid < 0){
            child = search(pid);
            child->status = status;
            if (errno == EINTR) {
                /* Este codigo de erro significa que chegou signal que interrompeu a espera
                   pela terminacao de filho; logo voltamos a esperar */
                free(child);
                continue;
            } else {
                perror("Unexpected error while waiting for child.");
                exit (EXIT_FAILURE);
            }
        }
        return;
    }
}

void printChildren() {
    for (int i = 0; i < vector_getSize(children); ++i) {
        child_t *child = vector_at(children, i);
        int status = child->status;
        pid_t pid = child->pid;
        if (pid != -1) {
            const char* ret = "NOK";
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                ret = "OK";
            }
            printf("CHILD EXITED: (PID=%d; return %s; %f s)\n", pid, ret, child->total_time);
        }
    }
    puts("END.");
}

child_t* search(int pid){
    for(int i = 0; i < vector_getSize(children); i++) {
        child_t* child = vector_at(children, i);
        if(child->pid == pid){
            return child;
        }
    }
    return NULL;
}

void create_child(pid_t pid, struct timeval time){
    child_t *child = malloc(sizeof(child_t));
    if (child == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    child->pid = pid;
    child->start_time = time;
    vector_pushBack(children, child);
}

void sigchld(int sig, siginfo_t *signal, void* c){
    struct timeval stop_time;
    TIMER_READ(stop_time);
    child_t* child = search(signal->si_pid); 

    double total_time = TIMER_DIFF_SECONDS(child->start_time, stop_time);

    if(child != NULL){
        if(signal->si_code == CLD_EXITED || CLD_KILLED || CLD_DUMPED){
            child->total_time = total_time;
        }
    }
}

int main (int argc, char** argv) {

    char *args1[MAXARGS + 1];
    char *args2[MAXARGS + 1];
    char buffer[BUFFER_SIZE];
    char buffer_read[BUFFER_SIZE];
    char name_exec[BUFFER_SIZE];
    int fcli, fserv;
    int MAXCHILDREN = -1;
    int runningChildren = 0;  

    struct sigaction sa;
    if(sigemptyset(&sa.sa_mask) == -1){
        perror("error: sigemptyset failed\n");
    }
    sa.sa_flags = SA_NOCLDSTOP | SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = sigchld;
    if(sigaction(SIGCHLD, &sa, NULL) == -1){
        printf("error: sigaction failed\n");
    }

    strcpy(name_exec, 2 + argv[0]);
    strcat(name_exec, ".pipe");
    unlink(name_exec); /*nao usamos safe_unlink pois iria retornar erro sem ser suposto*/
    /* Criacao do pipe 2(clients->shell) */
    safe_mkfifo(name_exec, 0777);

    fd_set read_fds;
    fserv = safe_open(name_exec, O_RDWR);

    if(argv[1] != NULL){
        MAXCHILDREN = atoi(argv[1]);
    }

    children = vector_alloc(MAXCHILDREN);
    printf("Welcome to CircuitRouter-AdvShell\n\n");


    while (1){
        FD_ZERO(&read_fds);
        FD_SET(fileno(stdin), &read_fds);
        FD_SET(fserv, &read_fds);

        int maxDescriptor = fileno(stdin) > fserv ? fileno(stdin) : fserv;
        int rv = select(maxDescriptor + 1, &read_fds, NULL, NULL, NULL);
        if(rv == -1){
            if(errno == EINTR){
                continue;
            }
            perror("error\n");
        }else{
            /*leitura do stdin da shell*/
            if(FD_ISSET(fileno(stdin), &read_fds)){
                int Args = readLineArguments(args1, MAXARGS + 1, buffer, BUFFER_SIZE, 1);
                if (Args < 0 || (Args > 0 && (strcmp(args1[0], COMMAND_EXIT) == 0))) {
                    printf("CircuitRouter-AdvShell will exit.\n--\n");

            /* Espera pela terminacao de cada filho */
                    while (runningChildren > 0) {
                        waitForChild();
                        runningChildren --;
                    }

                    printChildren();
                    safe_unlink(name_exec);
                    printf("--\nCircuitRouter-AdvShell ended.\n");
                    break;
                }else if (Args > 0 && strcmp(args1[0], COMMAND_RUN) == 0){
                    int pid;
                    if (Args < 2) {
                        printf("Command not supported\n");
                        continue;
                    }
                    if (MAXCHILDREN != -1 && runningChildren >= MAXCHILDREN) {
                        waitForChild();
                        runningChildren--;
                    }

                    pid = fork();
                    if (pid < 0) {
                        perror("Failed to create new process.");
                        exit(EXIT_FAILURE);
                    }

                    if (pid > 0) {
                        struct timeval start_time;
                        TIMER_READ(start_time);
                        create_child(pid, start_time);
                        runningChildren++;
                        printf("%s: background child started with PID %d.\n\n", COMMAND_RUN, pid);
                        continue;

                    } else {
                        char seqsolver[] = "../CircuitRouter-SeqSolver/CircuitRouter-SeqSolver";
                        char *newArgs[3] = {seqsolver, args1[1], NULL};

                        execv(seqsolver, newArgs);
                        perror("Error while executing child process"); // Nao deveria chegar aqui
                        exit(EXIT_FAILURE);
                    }
                }else if (Args == 0){
                    /* Nenhum argumento; ignora e volta a pedir */
                    continue;
                }else{
                    printf("Command not supported.\n");
                }
            }

            /*leitura do pipe*/
            if(FD_ISSET(fserv, &read_fds)) {
                /*char buffer_read = safe_read(fserv, buffer_read, BUFFER_SIZE);*/
                if(read(fserv, buffer_read, BUFFER_SIZE) == -1){
                    perror("error: read failed\n");
                }
                int Args = readLineArguments(args2, MAXARGS + 1, buffer_read, BUFFER_SIZE, 0);
                if(Args == 1){
                    fcli = safe_open(args2[Args - 1], O_WRONLY);
                    safe_write(fcli, "Command not supported\n", BUFFER_SIZE);
                    safe_close(fcli);
                }else if(Args > 0 && strcmp(args2[0], COMMAND_RUN) == 0) {
                    if(Args < 3) {
                        fcli = safe_open(args2[Args -1], O_WRONLY);
                        safe_write(fcli, "Command not supported\n", BUFFER_SIZE);
                        safe_close(fcli);
                    }else{
                        if (MAXCHILDREN != -1 && runningChildren >= MAXCHILDREN) {
                            waitForChild();
                            runningChildren--;
                        }

                        int pid = fork();
                        if (pid < 0) {
                            perror("Failed to create new process.");
                            exit(EXIT_FAILURE);
                        }

                        if (pid > 0) {
                            struct timeval start_time;
                            TIMER_READ(start_time);
                            create_child(pid, start_time);
                            runningChildren++;
                            printf("%s: background child started with PID %d.\n\n", COMMAND_RUN, pid);
                            continue;
                        } else {
                            char seqsolver[] = "../CircuitRouter-SeqSolver/CircuitRouter-SeqSolver";
                            char *newArgs[4] = {seqsolver, args2[1], args2[2], NULL};

                        execv(seqsolver, newArgs);
                        perror("Error while executing child process"); // Nao deveria chegar aqui
                        exit(EXIT_FAILURE);
                        }
                             
                    }
                }else{
                    fcli = safe_open(args2[Args-1], O_WRONLY);
                    safe_write(fcli, "Command not supported\n", BUFFER_SIZE);
                    safe_close(fcli);
                }
            }

        }
    }
    for (int i = 0; i < vector_getSize(children); i++) {
        free(vector_at(children, i));
    }
    vector_free(children);
    return EXIT_SUCCESS;
}
