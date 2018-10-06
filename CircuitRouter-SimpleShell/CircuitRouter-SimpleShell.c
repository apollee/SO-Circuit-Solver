/* ============================================================================= * 
* CircuitRouter-SeqSolver.c 
* 
* ============================================================================= 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "commandlinereader.h"
#include "../lib/list.h"
#include "run_command.h"

#define BUFFERSIZE 500
#define MAXARGS 5

#define COMMAND_RUN "run"
#define COMMAND_EXIT "exit"

int counter = 0;

int main(int argc, char** argv){
    int max_children = -1;
    list_t* list_pids = list_alloc(NULL);   

 
    if(argc == 2){
        max_children = atoi(argv[1]);
    }

  
    while(1){
        char *args[MAXARGS + 1]; 
        char buffer[BUFFERSIZE];
    
        int number_args = readLineArguments(args, MAXARGS + 1, buffer, BUFFERSIZE);
    
        /*if no argument is inserted then the program will keep waiting for valid user input*/
        if(number_args == 0){
            continue;
        }
 
        /*command exit*/
        if(strcmp(args[0], COMMAND_EXIT) == 0){
            if(number_args >= 2){
                printf("Invalid sintax, try again.\n");
                continue;
            }
            break;
            /*wait for processes to finish and end program*/
        }

 
        /*command run*/ 
        else if(strcmp(args[0], COMMAND_RUN) == 0){
            if(number_args < 2 || number_args >= 3){
                printf("Invalid syntax, try again.\n");
                continue;
            }

            if(access(args[1], R_OK) == -1){
                printf("File doesnt exist, try again.\n");
                continue;
            }
            counter++;
            start_process(max_children, args[1], list_pids, counter);
            /*exec file_name and start process*/
        }
        

        else{
            printf("Invalid sintax or unknown command, try again.\n");
        }
        
    }
    return 0;
}      
