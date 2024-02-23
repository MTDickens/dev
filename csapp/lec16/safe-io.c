#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

ssize_t Write(int fd, void *buf, size_t count)
{
    ssize_t retval;
    if ((retval = write(fd, buf, count)) < 0) {
        perror("write");
        exit(1);
    }
    return retval;
}

ssize_t Read(int fd, void *buf, size_t count)
{
    ssize_t retval;
    if ((retval = read(fd, buf, count)) < 0) {
        perror("read");
        exit(1);
    }
    return retval;
}

int Close(int fd)
{
    int retval;
    if ((retval = close(fd)) < 0)
    {
        perror("close");
        exit(1);
    }
    return retval;
}

int Open(const char *file, int oflag)
{
    int fd;
    if ((fd = open(file, oflag)) < 0)
    {
        perror("open");
        exit(1);
    }
    return fd;
}