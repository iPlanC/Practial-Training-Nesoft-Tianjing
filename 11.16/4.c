#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t sem;

void *thread1(void *arg);
void *thread2(void *arg);

int main() {
    pthread_t pthread1 = 0;
    pthread_t pthread2 = 0;
    if (sem_init(&sem, 0, 0) == -1) perror("sem_init(&sem, 0, 0)");
    pthread_create(&pthread1, NULL, thread1, (void *)0);
    pthread_create(&pthread2, NULL, thread2, (void *)0);

    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);

    return 0;
}

void *thread1(void *arg) {
    int i = 10;
    while (i--) {
        sem_post(&sem);
        printf("thread1: posted\n");
        sleep(1);
    }
    return NULL;
}

void *thread2(void *arg) {
    int i = 5;
    while (i--) {
        sem_wait(&sem);
        printf("thread2: recived\n");
        sleep(1);
    }
    return NULL;
}