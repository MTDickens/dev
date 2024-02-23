#include "safe-io.h"
#include <string.h>

int main() {
    int fd_out = STDOUT_FILENO;
    int fd_in = STDIN_FILENO;

    char str1[] = "Where are you from?\n";
    char str2[] = "Well, hello! My friend from ";
    char str3[] = "!\n";

    char read_buf[514];
    memset(read_buf, 0, sizeof(read_buf));

    Write(fd_out, str1, sizeof(str1));
    Read(fd_in, read_buf, sizeof(read_buf) - 1);
    Write(fd_out, str2, sizeof(str2));
    Write(fd_out, read_buf, strlen(read_buf) - 1);
    Write(fd_out, str3, sizeof(str3));

    Close(fd_out);

    return 0;
}