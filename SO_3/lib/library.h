#ifndef LIBRARY_H
#define LIBRARY_H

#include <unistd.h>
#include <sys/stat.h>

void safe_unlink(const char* pathname);
void safe_mkfifo(const char* pathname, mode_t mode);
void safe_write(int pipe, const void* buf, size_t buffer);
int safe_open(const char* pathname, int flag);
char* safe_read(int pipe, void* buffer_read, size_t buffer);
void safe_close(int pipe);

#endif