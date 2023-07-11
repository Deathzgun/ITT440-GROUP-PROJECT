//Client


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8484

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char input[1024] = {0};
    char buffer[1024] = {0};

    // Create socket file descriptor
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "192.168.33.132", &(server_address.sin_addr)) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // Get user input string
    printf("Enter your text: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    // Send the user input string to the server
    send(client_socket, input, strlen(input), 0);
    printf("Text sent to the server.\n");

    // Receive the reply from the server
    read(client_socket, buffer, 1024);
    printf("Reply from server: %s\n", buffer);

    // Close the socket
    close(client_socket);

    return 0;
}
