#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

#define MAX_LEN 64

/* client.c */
int main(int argc, char *argv[])
{
    // Variables
    char *host;
    int port;
    struct sockaddr_in sad;
    struct hostent *ptrh;
    int clientSocket;
    char sent_sentence[MAX_LEN];
    char retrieved_sentence[MAX_LEN];

    // Get the host and the port
    host = argv[1];
    port = atoi(argv[2]);

    // Retrieve the ip of the domain
    ptrh = gethostbyname(host);

    // Create socket descriptor
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    // Construct the socket address
    memset(&sad, 0, sizeof(sad));

    sad.sin_family = AF_INET;
    sad.sin_port = htons((u_int16_t)port);
    memcpy(&sad.sin_addr, ptrh->h_addr_list[0], ptrh->h_length);

    // Activate the socket
    if (connect(clientSocket, (struct sockaddr *)&sad, sizeof(sad)) < 0)
    {
        printf("Connection failed :(\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Connection succeeded!\n");
    }

    scanf("%s", sent_sentence);
    printf("Scanf finished!\n");

    write(clientSocket, sent_sentence, strlen(sent_sentence) + 1);
    printf("Sentenced sent! Waiting for reply...\n");
    read(clientSocket, retrieved_sentence, sizeof(retrieved_sentence));

    printf("FROM SERVER: %s\n", retrieved_sentence);

    close(clientSocket);

    return 0;
}