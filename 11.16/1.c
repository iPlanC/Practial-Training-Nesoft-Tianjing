#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    sem_t *sem_f2c;
    sem_t *sem_c2f;
    sem_f2c = (sem_t *)mmap(NULL, sizeof(sem_f2c), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_c2f = (sem_t *)mmap(NULL, sizeof(sem_c2f), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (sem_init(sem_c2f, 1, 0) == -1) perror("sem_init(&sem_c2f, 1, 0)");
    if (sem_init(sem_f2c, 1, 0) == -1) perror("sem_init(&sem_f2c, 1, 0)");
    sem_post(sem_c2f);

    pid_t pid = fork();

    if (pid == 0) {
        while (1) {
            sem_wait(sem_f2c);
            printf("Child:  Hello World\n");
            sem_post(sem_c2f);
        }
    }

    if (pid > 0) {
        while (1) {
            sem_wait(sem_c2f);
            printf("Parent: Good Morning\n");
            sem_post(sem_f2c);
        }
    }

    if (pid < 0) perror("fork()");
    return 0;
}