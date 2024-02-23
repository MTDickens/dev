#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void fork2()
{
    printf("L0\n");
    fork();
    printf("L1\n");
    fork();
    printf("Bye\n");
}

void fork4()
{
    printf("L0\n");
    if (fork() != 0)
    { /* if not child process */
        printf("L1\n");
        if (fork() != 0)
        { /* if not child process */
            printf("L2\n");
        }
    }
    printf("Bye\n");
}

void fork5()
{
    printf("L0\n");
    if (fork() == 0)
    {
        printf("L1\n");
        if (fork() == 0)
        {
            printf("L2\n");
        }
    }
    printf("Bye\n");
}

int main()
{
    fork5();
    return 0;
}