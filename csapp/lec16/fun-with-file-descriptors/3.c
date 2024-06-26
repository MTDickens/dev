#include "../../csapp.h"
int main(int argc, char *argv[])
{
    int fd1, fd2, fd3;
    char *fname = argv[1];
    fd1 = Open(fname, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
    Write(fd1, "pqrs", 4);                     // pqrs
    fd3 = Open(fname, O_APPEND | O_WRONLY, 0); // pqrs
    Write(fd3, "jklmn", 5);                    // pqrsjklmn
    fd2 = dup(fd1);                            /* Allocates descriptor */
    Write(fd2, "wxyz", 4);                     // pqrswxyzn
    Write(fd3, "ef", 2);                       // pqrswxyznef
    return 0;
}
