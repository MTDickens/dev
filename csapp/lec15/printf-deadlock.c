#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// 信号处理函数
void signalHandler(int signal) {
    printf("Received signal: %d\n", signal);
    exit(0);
}

int main() {

    // 注册信号处理函数
    signal(SIGINT, signalHandler);

    printf("Hello world\n");
    while(1) {
        // 无限循环，等待信号
    }

    return 0;
}
