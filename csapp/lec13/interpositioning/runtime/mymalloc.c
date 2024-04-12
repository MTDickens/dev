#ifdef RUNTIME
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void *malloc(size_t size)
{  
    static int calltimes = 0;
    calltimes++;

    void *(*mallocp)(size_t size);
    char *error;

    mallocp = dlsym(RTLD_NEXT, "malloc"); /* Get address of libc   malloc */ 
    if ((error = dlerror()) != NULL) { 
        --calltimes;
        fputs(error, stderr);
        exit(1);
    }
    char *ptr = mallocp(size); /* Call libc malloc */
    if (calltimes == 1)
        printf("malloc(%d) = %p\n", (int)size, ptr);
    --calltimes;
    return ptr;
}

/* free wrapper function */
void free(void *ptr)
{
    static int calltimes = 0;
    calltimes++;

    void (*freep)(void *) = NULL;
    char *error;

    if (!ptr)
    return;

    freep = dlsym(RTLD_NEXT, "free"); /* Get address of libc free */
    if ((error = dlerror()) != NULL) {
        --calltimes;
        fputs(error, stderr);
        exit(1);
    }
    freep(ptr); /* Call libc free */
    if (calltimes == 1)
        printf("free(%p)\n", ptr);
    --calltimes;
}
#endif