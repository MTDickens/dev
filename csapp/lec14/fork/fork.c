#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Hello from child process!\n");
    } else {
        // Parent process
        printf("Hello from parent process!\n");
    }

    return 0;
}
