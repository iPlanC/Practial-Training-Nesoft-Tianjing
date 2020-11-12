#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void SIG_Handler(int signum);

int main() {
    printf("pid = %d\n", getpid());

    signal(SIGINT, SIG_Handler);
    signal(SIGQUIT, SIG_Handler);
    while (1) {
        printf("Hello\n");
        sleep(1);
    }
    return 0;
}

void SIG_Handler(int signum) {
    if (signum == SIGINT) {
        printf("detect SIGINT\n");
        exit(1);
    }
    if (signum == SIGQUIT) {
        printf("detect SIGQUIT\n");
    }
}
