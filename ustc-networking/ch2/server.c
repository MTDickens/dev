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
    int welcome_socket, connection_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len;
    char buffer[MAX_LINE];

    // Create socket
    welcome_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (welcome_socket < 0)
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
    if (bind(welcome_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    signal(SIGINT, sigint_handler);

    // Listen for incoming connections
    if (listen(welcome_socket, MAX_PENDING) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (!sigint_flag)
    {
        // Accept connection
        client_address_len = sizeof(client_address);
        connection_socket = accept(welcome_socket, (struct sockaddr *)&client_address, &client_address_len);
        if (connection_socket < 0)
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        printf("Client connected: %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        // Receive data from client
        ssize_t bytes_received = recv(connection_socket, buffer, MAX_LINE, 0);
        if (bytes_received < 0)
        {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        // Append "Echo: " to received data
        memcpy(buffer + 6, buffer, bytes_received);
        memcpy(buffer, "Echo: ", 6);

        // Send echoed data back to client
        ssize_t bytes_sent = send(connection_socket, buffer, bytes_received + 6, 0);
        if (bytes_sent < 0)
        {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }

        // Close connection
        close(connection_socket);
    }

    if (sigint_flag)
    {
        printf("Connection closed. Bye!\n");
        close(connection_socket);
        return 0;
    }

    return 0;
}
