#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int i = 5;
    pid_t pid = 0;
    pid = vfork();
    if (pid > 0) {
        while (1) {
            printf("Hello\n");
            sleep(1);
        }
    }
    else {
        while (i--) {
            printf("World\n");
            sleep(1);
        }
    }
    return 0;
}
