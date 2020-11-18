#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//#define PORT_ID	8800
#define SIZE	400

int main(int argc, char *argv[])
{
    int sock_fd;
    struct sockaddr_in server_addr;
    int addr_len;
    char buf[SIZE];
    char flag;
    FILE *fp;

    if(argc != 3)
    {
        printf("Usage: ./client IP PORT\n");
        exit(1);
    }
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    //receive welcome message from server
    recv(sock_fd, buf, SIZE, 0);
    printf("Receive from server: %s\n", buf);
    memset(buf, '\0', SIZE);
    printf("Please input the directory and filename that you want to send to the sever:\n");
    scanf("%s", buf);
    if((fp = fopen(buf, "rb")) == NULL)
    {
        perror("fopen");
        close(sock_fd);
        exit(1);
    }
    //send path and filename to the sever
    send(sock_fd, buf, sizeof(buf), 0);
    //receive 'Y' or 'N' from server
    recv(sock_fd, &flag, sizeof(flag), 0);

    if(flag != 'Y')
    {
        printf("Sever refused to receive the file!\n");
        fclose(fp);
        close(sock_fd);
        exit(1);
    }
    printf("Begin to transmit\n");
    memset(buf, '\0', sizeof(buf));
    while(!feof(fp))
    {
    	memset(buf, '\0', sizeof(buf));
        fread(buf, 1, sizeof(buf) - 1, fp);
        send(sock_fd, buf, strlen(buf), 0);
        printf("%ld bytes sent\n", strlen(buf));
    }

    fclose(fp);
    close(sock_fd);
    return 0;
}