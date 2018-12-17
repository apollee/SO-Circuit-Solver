#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "library.h"

void safe_unlink(const char* pathname){
    if(unlink(pathname) == -1){
        perror("error: unlink failed\n");
    }
}

void safe_mkfifo(const char* pathname, mode_t permission){
    if(mkfifo(pathname, permission) == -1){
        perror("error: mkfifo failed\n");
        exit(-1);
    }
}

int safe_open(const char* pathname, int flag){
    int pipe;
    if((pipe = open(pathname, flag)) < 0) {
        perror("error: open failed\n");
        exit(-1);
    }
    return pipe;
}

void safe_close(int pipe){
    if(close(pipe) == -1){
        perror("error: closing the pipe failed\n");
    }
}

void safe_write(int pipe, const void* buf, size_t buffer){
    if(write(pipe, buf, buffer) == -1){
        perror("error: write failed\n");
    }
}
