#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char str[50];
char str1[50];

int main() {
    int pipefd[2];
    pid_t pid1 = 0;
    pipe(pipefd);
    pid1 = fork();
    if (pid1 == 0) {
        while (1) {
            close(pipefd[1]);
            read(pipefd[0], str1, strlen(str));
            printf("child  process, str = \"%s\"\n", str1);
            sleep(5);
        }
    }
    else if (pid1 > 0) {
        while (1) {
            close(pipefd[0]);
            printf("parent process, \n");
            scanf("%s", str);
            write(pipefd[1], str, strlen(str));
            sleep(5);
        }
    }
    else {
        printf("error\n");
    }
    return 0;
}
