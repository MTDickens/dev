#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    int *ptr = malloc(sizeof(int));
    *ptr = 0;
    int x = 1;

    pid_t pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        printf("Hello from child process! PID == %d, *ptr == %d, x == %d\n", pid, (*ptr += 114514), ++x);
    }
    else
    {
        // Parent process
        printf("Hello from parent process! PID == %d, *ptr == %d, x == %d\n", pid, (*ptr -= 1919810), --x);
    }

    return 0;
}
