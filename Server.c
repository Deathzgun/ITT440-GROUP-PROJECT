
//Server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define PORT 8484

int main() {
    int server_fd, client_socket, valread;
    struct sockaddr_in server_address;
    int opt = 1;
    int addrlen = sizeof(server_address);
    char buffer[1024] = {0};
    char reply[2048] = {0};  // Increase buffer size to 2048
    time_t current_time;
    char* server_time;

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the socket to the specified IP address and port
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept a new connection
        if ((client_socket = accept(server_fd, (struct sockaddr *)&server_address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Receive data from the client
        valread = read(client_socket, buffer, 1024);

        // Manipulate incoming text with server's current date and time
        current_time = time(NULL);
        server_time = ctime(&current_time);
        sprintf(reply, "%s received at %s", buffer, server_time);

        // Send the modified text back to the client
        send(client_socket, reply, strlen(reply), 0);
        printf("Reply sent to the client: %s\n", reply);

        // Close the client socket
        close(client_socket);
    }

    return 0;
}
