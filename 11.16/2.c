#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

int main() {
    int i = 10;
    sem_t *sem = sem_open("shsem", O_CREAT, 666, 0);
    while (i--) {
        sem_post(sem);
        sleep(1);
    }
    return 0;
}