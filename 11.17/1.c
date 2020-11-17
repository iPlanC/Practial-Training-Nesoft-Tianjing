#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define SERVER_PORT 8800

int main() {
    int sockaddr_in_size = sizeof(struct sockaddr_in);
    int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    int client_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[100] = {'\0'};
	time_t t;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);
    bind(server_sock_fd, (const struct sockaddr *)&server_addr, sockaddr_in_size);

    listen(server_sock_fd, 10);

    while (1) {
        printf("\nserver is waiting for connection...\n");
        client_sock_fd = accept(server_sock_fd, (struct sockaddr *)&client_addr, &sockaddr_in_size);

        if (strcmp("172.17.160.49", inet_ntoa(client_addr.sin_addr)) == 0) {
            printf("A blacklisted client connected ip: \"%s\", connection refused\n", inet_ntoa(client_addr.sin_addr));
            send(client_sock_fd, "localhost", sizeof("localhost"), 0);
            close(client_sock_fd);
            continue;
        }
		else {
			time(&t);
			strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", localtime(&t));
        	printf("A client connected ip: \"%s\"\n", inet_ntoa(client_addr.sin_addr));
        	send(client_sock_fd, buffer, sizeof(buffer), 0);
        	printf("sent time is: \"%s\"\n", buffer);
        	close(client_sock_fd);
        }
    }
    close(server_sock_fd);

    return 0;
}