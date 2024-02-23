#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void fork9()
{
    int child_status;
    if (fork() == 0)
    {
        printf("HC: hello from child\n");
        exit(0);
    }
    else
    {
        printf("HP: hello from parent\n");
        wait(&child_status);
        printf("CT: child has terminated\n");
    }
    printf("Bye\n");
}

int main() 
{
    fork9();
    return 0;
}