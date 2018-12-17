#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "lib/commandlinereader.h"
#include "../lib/library.h"

#define COMMAND_RUN "run"

#define BUFFER_SIZE 100

int main(int argc, char** argv) {

    static char template[] = "../CircuitRouter-Client/fileXXXXXX";
    char buf[BUFFER_SIZE];
    char path[BUFFER_SIZE];
    char fname[BUFFER_SIZE];
    int fserv, fcli;
    
    
    if(argv[1] != NULL) {
        strcpy(path, argv[1]);
    }else {
        printf("Missing arguments\n");
        exit(-1);
    }


    strcpy(fname, template);
    int fd = mkstemp(fname);
    if(fd == -1){
        perror("error: mkstemp failed.\n");
        exit(-1);
    }
    strcat(fname, ".pipe");

    safe_mkfifo(fname, 0777);
    fcli = safe_open(fname, O_RDWR);

    
    fserv = safe_open(path, O_WRONLY); 
    printf("Welcome to CircuitRouter-Client\n\n");

    while(1) {
        fgets(buf, BUFFER_SIZE, stdin);
        for(int i = 0; i < strlen(buf); i++){
        	if(buf[i] == '\n'){
            	buf[i] = '\0';
        	}
        }
        strcat(buf, " ");
        strcat(buf, fname);
        if(buf != NULL){
            safe_write(fserv, buf, BUFFER_SIZE);
        }
       	int n = read(fcli, buf, BUFFER_SIZE);
        if(n <= 0){
            perror("error: read failed\n");
        }
       	printf("%s", buf);       
    }
    safe_close(fserv);
    safe_close(fcli);
}