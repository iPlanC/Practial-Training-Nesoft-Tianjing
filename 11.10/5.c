#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char chr1 = 'a';
char chr2;

int main() {
    int pipefd1[2];
    int pipefd2[2];
    pid_t pid1 = 0;

    pipe(pipefd1);
    pipe(pipefd2);

    pid1 = fork();
    if (pid1 > 0) {
        while (1) {
            close(pipefd1[1]);
            close(pipefd2[0]);

            write(pipefd1[0], &chr1, 1);
            read(pipefd2[1], &chr1, 1);
            printf("Parent char = \"%c\"\n", chr1);

            sleep(1);
        }
    }
    else if (pid1 == 0) {
        while (1) {
            close(pipefd1[0]);
            close(pipefd2[1]);

            read(pipefd1[1], &chr2, 1);
            chr2 = chr2 + 'A' - 'a';
            write(pipefd2[0], &chr2, 1);
            printf("child  char = \"%c\"\n", chr2);

            sleep(1);
        }
    }
    else {
        printf("error\n");
    }
    return 0;
}
