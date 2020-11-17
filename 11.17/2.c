#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SERVER_PORT 8800

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage %s <ip>\n", argv[0]);
    }

    int sockaddr_in_size = sizeof(struct sockaddr_in);
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(SERVER_PORT);

    connect(sock_fd, (const struct sockaddr *)&server_addr, sockaddr_in_size);

    return 0;
}