#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LENGTH 200

int main(int argc, char* argv[]) {
  char input[MAX_LENGTH] = {0};

  int fd = open("io-redirection.txt", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
  dup2(fd, 1);

  fgets(input, MAX_LENGTH, stdin);  // 从标准输入获取输入
  printf("%s", input);  // 输出到标准输出

  close(fd);
  return 0;
}