/* ============================================================================= * 
* CircuitRouter-SeqSolver.c 
* 
* ============================================================================= 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include "commandlinereader.h"
#include "../lib/list.h"
#include "CircuitRouter-SimpleShell.h"

typedef struct process{
    int pid;
    int status;
}*process_t;    


int main(int argc, char** argv){
    int max_children;
    list_t* list_pids = list_alloc(NULL);   

 
    if(argc == 2){
        max_children = atoi(argv[1]);
    }

    if(max_children == 0){
        /*IGNORE IT;*/
        printf("ignore max_children\n");
    }


  
    while(1){
        char *args[MAXARGS + 1]; 
        char buffer[BUFFERSIZE];
        char *file_name = malloc(sizeof(char) * 500);
            
    
        int number_args = readLineArguments(args, MAXARGS + 1, buffer, BUFFERSIZE);
    
        /*if no argument is inserted then the program will keep waiting for valid user input*/
        if(number_args == 0){
            continue;
        }
 
        /*command exit*/
        if(strcmp(args[0], COMMAND_EXIT) == 0){
            if(number_args >= 2){
                printf("Invalid sintax for the command %s, try again.\n", COMMAND_EXIT);
                continue;
            }
            break;
            /*wait for processes to finish and end program*/
        }

 
        /*command run*/ 
        else if(strcmp(args[0], COMMAND_RUN) == 0){
            if(number_args < 2 || number_args >= 3){
                printf("Invalid sintax for the command %s, try again.\n", COMMAND_RUN);
                continue;
            }
            file_name = args[1];
            start_process(max_children, file_name, list_pids);
            /*exec file_name and start process*/
        }
        

        else{
            printf("Invalid sintax or unknown command, try again.\n");
            continue;
        } 
        
    }
    return 0;
}      
