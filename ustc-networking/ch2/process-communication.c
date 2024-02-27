#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2]; // 管道文件描述符数组
    pid_t pid;
    FILE *write_fd, *read_fd;
    

    if (pipe(pipefd) == -1) { // 创建管道
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork(); // 创建子进程

    if (pid == -1) { // 创建失败
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // 子进程
        char buffer[1024];
        close(pipefd[1]); // 关闭写入端
        read_fd = fdopen(pipefd[0], "r"); // 将管道读取端转换为 FILE*

        // 从管道中读取数据
        fread(buffer, sizeof(buffer) / sizeof(char), sizeof(char), read_fd);
        printf("Child process received: %s\n", buffer);
        

        fclose(read_fd); // 关闭 FILE*
        exit(EXIT_SUCCESS);
    } else { // 父进程
        close(pipefd[0]); // 关闭读取端
        write_fd = fdopen(pipefd[1], "w"); // 将管道写入端转换为 FILE*

        // 向管道中写入数据
        const char* message = "Haiyaa! So weak!";
        printf("Parent process sending: %s\n", message);
        fprintf(write_fd, "%s", message);
        fflush(write_fd); // 刷新缓冲区

        fclose(write_fd); // 关闭 FILE*
        wait(NULL); // 等待子进程退出
        exit(EXIT_SUCCESS);
    }

    return 0;
}
