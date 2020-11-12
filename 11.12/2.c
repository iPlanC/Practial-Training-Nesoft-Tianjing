#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main() {
    pid_t pid = 0;
    pid = fork();
    if (pid == 0) {
        while (1) {
            printf("Hello\n");
            sleep(1);
        }
    }

    if (pid > 0) {
        sleep(5);
        kill(pid, SIGINT);
    }

    if (pid < 0) {
        perror("error");
    }
    return 0;
}
