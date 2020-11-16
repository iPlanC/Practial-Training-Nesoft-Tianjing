#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    sem_t *sem = sem_open("shsem", O_CREAT, 666, 0);
    while (1) {
        sem_wait(sem);
        printf("recived sem from ./2.out\n");
    }
    return 0;
}