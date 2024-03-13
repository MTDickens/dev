#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>

#define PORT 11451
#define MAX_PENDING 10
#define MAX_LINE 1024

volatile sig_atomic_t sigint_flag;

void sigint_handler(int sig)
{
    int old_errno = errno;
    sigint_flag = 1;
    errno = old_errno;
}

int main()
{
    int sock;
    struct sockaddr_in server_address, client_address;
    socklen_t addr_len;
    char buffer[MAX_LINE];

    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    // Bind socket
    if (bind(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    signal(SIGINT, sigint_handler);

    while (!sigint_flag)
    {
        // Accept connection
        addr_len = sizeof(client_address);

        // Receive data from client
        ssize_t bytes_received = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_address, &addr_len);
        if (bytes_received < 0)
        {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        printf("Received %zd bytes from %s:%d\n", bytes_received, inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
        printf("Data: %.*s\n", (int)bytes_received, buffer);

        // Append "Echo: " to received data
        memcpy(buffer + 6, buffer, bytes_received);
        memcpy(buffer, "Echo: ", 6);

        // Send echoed data back to client
        ssize_t bytes_sent = sendto(sock, buffer, strlen(buffer) + 1, 0, (struct sockaddr *)&client_address, addr_len);
        if (bytes_sent < 0)
        {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }
    }

    if (sigint_flag)
    {
        printf("Connection closed. Bye!\n");
        close(sock);
        return 0;
    }

    return 0;
}
