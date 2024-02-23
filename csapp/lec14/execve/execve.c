#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void unix_error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

int Fork() {
    int pid;

    if ((pid = fork()) < 0) {
        unix_error("Fork error");
    }

    return pid;
}

int main(int argc, char *argv[]) {
    char *environ[] = { NULL };

    int pid;

    for (char **argv_ptr = argv; *argv_ptr != NULL; ++argv_ptr) {
        printf("Argv[%ld]: %s\n", argv_ptr - argv, *argv_ptr);
    }
    printf("\n" "We will execute %s with\n", argv[1]);
    for (char **argv_ptr = argv + 1; *argv_ptr != NULL; ++argv_ptr) {
        printf("Argv[%ld]: %s\n", argv_ptr - argv, *argv_ptr);
    }
    printf("\n");

    if ((pid = Fork()) == 0) {
        
        if (execve(argv[1], argv + 1, environ) < 0) {
            printf("%s Command not found.\n", argv[1]);
            exit(1);
        }
    }
    return 0;
}
