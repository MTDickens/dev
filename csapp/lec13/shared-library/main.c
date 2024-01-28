#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

long x[2] = {1, 2};
long y[2] = {3, 4};
long z[2];
void (* addvec) (long *v1, long *v2, long *vdest, unsigned int size);

int main()
{
    void *handle;
    char *error;

    handle = dlopen("./libvector.so", RTLD_LAZY);
    if (handle == NULL)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    addvec = dlsym(handle, "addvec");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    addvec(x, y, z, 2);
    printf("z = [%ld %ld]\n", z[0], z[1]);

    /* Unload the shared library */
    if (dlclose(handle) < 0)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    return 0;
}