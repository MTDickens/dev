// main.c
#include <stdio.h>

int food()
{
    return 114514;
}
int x = 114514;
extern int x;

int main()
{
    printf("%d %d\n", food(), x);
    return 0;
}