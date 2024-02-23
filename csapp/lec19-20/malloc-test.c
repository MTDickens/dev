#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define P_SIZE 1
#define Q_SIZE 24

int main() {
    int *p = malloc(P_SIZE);
    int *q = malloc(Q_SIZE);
    *p = 0x114514;
    *q = 0x1919810;
    memset(p, 0xae, P_SIZE);
    memset(q, 0xae, Q_SIZE);
    free(p);
    free(q);
    return 0;
}