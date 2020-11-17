#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 8800

int main() {
    int sockaddr_in_size = sizeof(struct sockaddr_in);
    int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    int client_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);
    bind(server_sock_fd, (const struct sockaddr *)&server_addr, sockaddr_in_size);

    listen(server_sock_fd, 10);

    while (1) {
        printf("server is waiting for connection...\n\n");
        client_sock_fd = accept(server_sock_fd, (struct sockaddr *)&client_addr, &sockaddr_in_size);
        printf("A client connected ip: \"%s\"\n", inet_ntoa(client_addr.sin_addr));
    }
    close(server_sock_fd);

    return 0;
}