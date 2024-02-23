#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#define N 10

volatile sig_atomic_t ccount = N;

void child_handler(int sig) {
    int olderrno = errno;
    pid_t pid;
    sig_atomic_t original_ccount = ccount;
    while ((pid = waitpid(-1, NULL, 0)) > 0) { 
        /** Change the third argument of `waitpid` to WNOHANG,
         *  if you don't want to wait for running child processes
         *  and only try to reap those zombie child processes.
         */
        ccount--;
        fprintf(stderr,"Handler reaped child ""%ld"" \n", (long) pid);
    }
    if (errno != ECHILD) fprintf(stderr, "errno: %d, error: %s\n", errno, strerror(errno));
    fprintf(stderr, "Reap finished for now! ccount: %d -> %d\n", original_ccount, ccount);
    errno = olderrno;
}
int main()
{
    sigset_t block_child, prev;
    sigemptyset(&block_child);
    sigaddset(&block_child, SIGCHLD);
    signal(SIGCHLD, child_handler);

    sigprocmask(SIG_BLOCK, &block_child, &prev);
    for (int i = 0; i != N; ++i) {
        int pid;
        if ((pid = fork()) == 0) { /* child process */
            sigprocmask(SIG_SETMASK, &prev, NULL);
            sleep(1);
            printf("I have slept for %d seconds\n", 1);
            exit(0);
        }
    }

    while (ccount > 0)
        sigsuspend(&prev);
    sigprocmask(SIG_SETMASK, &prev, NULL);

    return 0;
}