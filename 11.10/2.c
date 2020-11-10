#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int i = 0;

int main() {
    int pipefd[2];
    pid_t pid1 = 0;
    pipe(pipefd);
    pid1 = fork();
    if (pid1 == 0) {
        while (1) {
            close(pipefd[1]);
            read(pipefd[0], &i, 1);
            printf("child  process, i = %d\n", i);
            sleep(1);
        }
    }
    else if (pid1 > 0) {
        while (1) {
            close(pipefd[0]);
            write(pipefd[1], &i, 1);
            printf("parent process, i = %d\n", i++);
            sleep(1);
        }
    }
    else {
        printf("error\n");
    }
    return 0;
}