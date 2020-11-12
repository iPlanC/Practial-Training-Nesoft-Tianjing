#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    int shmid = 0;
    pid_t pid = 0;
    char str[] = "Hello";
    pid = fork();
    shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT);

    if (pid == 0) {
        char *c_addr;
        c_addr = shmat(shmid, NULL, 0);
        printf("%s\n", c_addr);
        shmdt(c_addr);
    }
    if (pid > 0) {
        char *p_addr;
        p_addr = shmat(shmid, NULL, 0);
        memset(p_addr, '\0', sizeof(str));
        memcpy(p_addr, str, sizeof(str));
        shmdt(p_addr);
    }
    if (pid < 0) {
        perror("error");
    }

    return 0;
}
