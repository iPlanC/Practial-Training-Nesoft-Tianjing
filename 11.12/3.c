#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void SIG_Handler(int signum);

int main() {
    signal(SIGALRM, SIG_Handler);
    alarm(1);
    printf("Hello\n");
    pause();
    return 0;
}

void SIG_Handler(int signum) {
    if (signum == SIGALRM) {
        printf("Time Up\n");
    }
}
