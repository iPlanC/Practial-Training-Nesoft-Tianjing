#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define SERVER_PORT 8800

int client_sock_fd;
int server_sock_fd;

void *trans(void *arg);

int main() {
	pthread_t thread = 0;
    int sockaddr_in_size = sizeof(struct sockaddr_in);
    client_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);
    bind(server_sock_fd, (const struct sockaddr *)&server_addr, sockaddr_in_size);

    listen(server_sock_fd, 1);

    while (1) {
        printf("\nserver is waiting for connection...\n");
        client_sock_fd = accept(server_sock_fd, (struct sockaddr *)&client_addr, &sockaddr_in_size);
		pthread_create(&thread, NULL, trans, (void *)inet_ntoa(client_addr.sin_addr));
    }
    close(server_sock_fd);

    return 0;
}

void *trans(void *arg) {
	int i = 10;
	printf("client ip: \"%s\" has connected\n", (char *)arg);
	//send(client_sock_fd, strcat("Hello, ", (char *)arg), sizeof(strcat("Hello, ", (char *)arg)), 0);
	while (i--) {
		send(client_sock_fd, "Hello", sizeof("Hello"), 0);
		sleep(1);
	}
	close(client_sock_fd);
}