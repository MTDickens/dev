#ifndef SAFE_IO_H
#define SAFE_IO_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

ssize_t Write(int fd, void *buf, size_t count);
ssize_t Read(int fd, void *buf, size_t count);
int Close(int fd);
int Open(const char *file, int oflag);


#endif