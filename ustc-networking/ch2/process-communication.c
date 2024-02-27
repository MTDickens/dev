#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define READ 0
#define WRITE 1

int main() {
    /**
     * 管道文件描述符数组
     * pipefd[0] is for read
     * pipefd[1] is for write
    */
    int pipefd[2];
    pid_t pid;    

    if (pipe(pipefd) == -1) { // 创建管道
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t read_fd = pipefd[READ], write_fd = pipefd[WRITE];

    pid = fork(); // 创建子进程

    if (pid == -1) { // 创建失败
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // 父进程向子进程传递 msg
    if (pid == 0) { // 子进程
        char buffer[1024];
        close(write_fd); // 关闭 write_fd

        // 从管道中读取数据
        read(read_fd, buffer, sizeof(buffer));
        printf("Child process received: %s\n", buffer);
        
        close(read_fd); // 关闭 read_fd
        exit(EXIT_SUCCESS);
    } else { // 父进程
        close(read_fd); // 关闭 read_fd

        const char msg[] = "Fuiyoh! Nice tossing! Uncle Roger impressed~";
        //  向管道写数据
        write(write_fd, msg, sizeof(msg));
        printf("Parent process sent: %s\n", msg);
        
        close(write_fd); // 关闭 write_fd
        exit(EXIT_SUCCESS);
    }

    return 0;
}
