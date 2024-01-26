int x = 0xa;
int y = 0x14;

#include <stdio.h>

void change();

int main() {
    change();
    printf("%x %x\n", x, y);
}