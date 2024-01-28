#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>

void *my_malloc(int size) {
    void *ptr = malloc(size);
    printf("malloc(%d) = %p\n", (int)size, ptr);
    return ptr;
}

void my_free(void *ptr)
{
    free(ptr);
    printf("free(%p)\n", ptr);
}

#endif