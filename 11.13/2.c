#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    int shmid = 0;
    key_t key = 0;
    key = ftok("ftok", 1);
    shmid = shmget(key, 1024, IPC_CREAT);

    char *c_addr;
    c_addr = shmat(shmid, NULL, 0);
    printf("%s\n", c_addr);
    shmdt(c_addr);

    return 0;
}
