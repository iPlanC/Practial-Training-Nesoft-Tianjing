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
	int i = 0;
    int sockaddr_in_size = sizeof(struct sockaddr_in);
    int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    int client_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    char ch = 0;
    char flag = 0;
    char buffer[400] = {'\0'};
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

        if (strcmp("0.0.0.0", inet_ntoa(client_addr.sin_addr)) == 0) {
            printf("A blacklisted client connected ip: \"%s\", connection refused\n", inet_ntoa(client_addr.sin_addr));
            send(client_sock_fd, "localhost", sizeof("localhost"), 0);
            close(client_sock_fd);
            continue;
        }
		else {
			printf("connected client ip: \"\%s\"\n", inet_ntoa(client_addr.sin_addr));
			send(client_sock_fd, "welcome to 39.106.19.94@Aliyun\n", sizeof("welcome to 39.106.19.94@Aliyun\n"), 0);
			recv(client_sock_fd, buffer, sizeof(buffer), 0);
			printf("client senf a file: \"%s\", accecpet file transmate? (Y/N)\n", buffer);
			scanf("%c", &flag);
			send(client_sock_fd, &flag, sizeof(flag), 0);

			if (flag == 'Y') {
				FILE *fp = fopen(strcat(buffer, ".recv"), "wb");
				if (fp == NULL) {
					perror("fopen");
					close(client_sock_fd);
					continue;
				}
				memset(buffer, '\0', sizeof(buffer));
				while (1) {
					if (recv(client_sock_fd, buffer, sizeof(buffer), 0) != 0) {
						fwrite(buffer, 1, sizeof(buffer), fp);
					}
					else {
						break;
					}
				}
				printf("reciving finished\n");
				fclose(fp);
			}
			else {
				printf("refused transmate\n");
			}
			close(client_sock_fd);
        }
    }
    close(server_sock_fd);

    return 0;
}