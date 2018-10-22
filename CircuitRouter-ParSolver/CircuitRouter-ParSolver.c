#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


long global_params[256];

int parseArgs (long argc, char* const argv[]){
     long opt;
     int num_tasks;
     opterr = 0;
  
     while ((opt = getopt(argc, argv, "t:")) != -1) {
         switch (opt) {
             case 't':
                 global_params[(unsigned char)opt] = atol(optarg);
                 break;
             default:
                 opterr++;
                 break;
         }
    }
    
    if(optind == argc){  
        num_tasks = atoi(argv[optind -1]);
        if(num_tasks > 0){
            return num_tasks; 
        }
    }

    fprintf(stderr, "Invalid input.\n");    
    exit(-1);
}

int main(int argc, char* argv[]){
    
    int num_tasks = parseArgs(argc, argv);
    printf("O num de tarefas e: %d\n", num_tasks);
    return 0;    
}




