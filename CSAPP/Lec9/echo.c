#include <stdio.h>
#include <stdlib.h>

void echo() {
    char buf[4];
    gets(buf);
    puts(buf);
}

void call_echo() {
    echo();
}

int main() {
    call_echo();
}