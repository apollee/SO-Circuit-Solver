#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "commandlinereader.h"
#include "commands.h"
#include "linked_l.h"
#include "circuit.h"
 
#define MAXARGS 5
#define BUFFERSIZE 500

#define COMMAND_RUN "run"
#define COMMAND_EXIT "exit"
#define ERROR_COMMAND "Invalid syntax, try again."

int counter = 0;

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
            exit_shell(max_children, head, counter);
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
            counter++;
            run(head, counter, max_children, args[1]);
        }

        else{
            printf("Invalid syntax or unknown command, try again.\n");
            continue;
        }
    }
    return 0;
}
