#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid1 = 0;
    pid_t pid2 = 0;
    pid1 = fork();
    pid2 = fork();
    printf("pid1 = %d,\tpid2 = %d\n", pid1, pid2);
    return 0;
}
