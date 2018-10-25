 /* =============================================================================
 *
 * CircuitRouter-ParSolver.c
 *
 * =============================================================================
 */


#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lib/list.h"
#include "maze.h"
#include "router.h"
#include "lib/timer.h"
#include "lib/types.h"

enum param_types {
    PARAM_BENDCOST = (unsigned char)'b',
    PARAM_XCOST    = (unsigned char)'x',
    PARAM_YCOST    = (unsigned char)'y',
    PARAM_ZCOST    = (unsigned char)'z',
    PARAM_THREADS  = (unsigned char)'t',
};

enum param_defaults {
    PARAM_DEFAULT_BENDCOST = 1,
    PARAM_DEFAULT_XCOST    = 1,
    PARAM_DEFAULT_YCOST    = 1,
    PARAM_DEFAULT_ZCOST    = 2,
    PARAM_DEFAULT_THREADS  = -1, /*default a -1 para rebentar*/ 
};

bool_t global_doPrint = FALSE;
char* global_inputFile = NULL;
long global_params[256]; /* 256 = ascii limit */


/* =============================================================================
 * displayUsage
 * =============================================================================
 */
static void displayUsage (const char* appName){
    printf("Usage: %s [options]\n", appName);
    puts("\nOptions:                            (defaults)\n");
    printf("    b <INT>    [b]end cost          (%i)\n", PARAM_DEFAULT_BENDCOST);
    printf("    p          [p]rint routed maze  (false)\n");
    printf("    x <UINT>   [x] movement cost    (%i)\n", PARAM_DEFAULT_XCOST);
    printf("    y <UINT>   [y] movement cost    (%i)\n", PARAM_DEFAULT_YCOST);
    printf("    z <UINT>   [z] movement cost    (%i)\n", PARAM_DEFAULT_ZCOST);
    printf("    t <UINT>   [t] number of threads (%i)\n", PARAM_DEFAULT_THREADS);
    printf("    h          [h]elp message       (false)\n");
    exit(1);
}


/* =============================================================================
 * setDefaultParams
 * =============================================================================
 */
static void setDefaultParams (){
    global_params[PARAM_BENDCOST] = PARAM_DEFAULT_BENDCOST;
    global_params[PARAM_XCOST]    = PARAM_DEFAULT_XCOST;
    global_params[PARAM_YCOST]    = PARAM_DEFAULT_YCOST;
    global_params[PARAM_ZCOST]    = PARAM_DEFAULT_ZCOST;
    global_params[PARAM_THREADS]  = PARAM_DEFAULT_THREADS;
}


/* =============================================================================
 * parseArgs
 * =============================================================================
 */
char* parseArgs (long argc, char* const argv[]){
    long opt;
    opterr = 0;

    setDefaultParams();

    while ((opt = getopt(argc, argv, "hb:x:y:z:t:")) != -1) {
        switch (opt) {
            case 'b':
            case 'x':
            case 'y':
            case 'z':
            case 't':
                global_params[(unsigned char)opt] = atol(optarg);
                break;
            case '?':
            case 'h':
            default:
                opterr++;
                break;
        }
    }
     
    if(optind ==  argc - 1){
        return argv[optind];
    }else if(optind > argc - 1){
        fprintf(stderr, "Non-optional arguments\n");
        opterr++;
    }else{
        fprintf(stderr, "No file name.\n");
    }


    if (opterr){ 
        displayUsage(argv[0]);
    }

    return NULL; 
}


/* =============================================================================
 * main
 * =============================================================================
 */
int main(int argc, char** argv){
    /*
     * Initialization
     */
    
    FILE *file;
    FILE *output_file; 
    char* file_input_name;
    char* file_output_name;
    int N_threads, i;

    file_input_name = parseArgs(argc, (char** const)argv);
    if (access(file_input_name, F_OK) != 0) { //input file exists
	fprintf( stderr, "The file doesn't exist.\n");
    	exit(1);
    }

    N_threads =  global_params[PARAM_THREADS];
    pthread_t tid[N_threads];
    
       file = fopen(file_input_name, "r");    
    file_output_name = output_fname(file_input_name); /*returns the name of the output file*/ 
    output_file = fopen(file_output_name, "a");

    maze_t* mazePtr = maze_alloc();
    assert(mazePtr);
    long numPathToRoute = maze_read(mazePtr, file, output_file);
    router_t* routerPtr = router_alloc(global_params[PARAM_XCOST],
                                       global_params[PARAM_YCOST],
                                       global_params[PARAM_ZCOST],
                                       global_params[PARAM_BENDCOST]);
    assert(routerPtr);
    list_t* pathVectorListPtr = list_alloc(NULL);
    assert(pathVectorListPtr);

    router_solve_arg_t routerArg = {routerPtr, mazePtr, pathVectorListPtr};
    TIMER_T startTime;
    TIMER_READ(startTime);

    for(i=0; i< N_threads; i++){    
        if(pthread_create(&tid[i], 0, (void *) router_solve, &routerArg) == 0){
            printf("Criada a tarefa %lu\n", tid[i]);
        }else{
            printf("Erro\n");
            exit(-1);
        }
    
    }
   

    /*router_solve((void *)&routerArg);*/

    TIMER_T stopTime;
    TIMER_READ(stopTime);

    long numPathRouted = 0;
    list_iter_t it;
    list_iter_reset(&it, pathVectorListPtr);
    while (list_iter_hasNext(&it, pathVectorListPtr)) {
        vector_t* pathVectorPtr = (vector_t*)list_iter_next(&it, pathVectorListPtr);
        numPathRouted += vector_getSize(pathVectorPtr);
	}
 
    fprintf(output_file, "Paths routed    = %li\n", numPathRouted);
    fprintf(output_file, "Elapsed time    = %f seconds\n", TIMER_DIFF_SECONDS(startTime, stopTime));

    /*
     * Check solution and clean up
     */
    assert(numPathRouted <= numPathToRoute);
    bool_t status = maze_checkPaths(mazePtr, pathVectorListPtr, output_file);
    assert(status == TRUE);
    fprintf(output_file, "Verification passed.");

    maze_free(mazePtr);
    router_free(routerPtr);

    list_iter_reset(&it, pathVectorListPtr);
    while (list_iter_hasNext(&it, pathVectorListPtr)) {
        vector_t* pathVectorPtr = (vector_t*)list_iter_next(&it, pathVectorListPtr);
        vector_t* v;
        while((v = vector_popBack(pathVectorPtr))) {
            // v stores pointers to longs stored elsewhere; no need to free them here
            vector_free(v);
        }
        vector_free(pathVectorPtr);
    }
    list_free(pathVectorListPtr);

    fclose(file);
    fclose(output_file);
    free(file_output_name);
    exit(0);
}


/* =============================================================================
 *
 * End of CircuitRouter-SeqSolver.c
 *
 * =============================================================================
 */    
