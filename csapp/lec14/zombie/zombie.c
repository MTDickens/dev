#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void fork7()
{
    if (fork() == 0) {
        printf("Terminating Child, PID = %d\n", getpid());
    } else {
        printf("Running Parent, PID = %d\n", getpid());
        while (1);
    }
}

int main() {
    fork7();
    return 0;
}