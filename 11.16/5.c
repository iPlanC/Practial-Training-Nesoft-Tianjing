#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex;

void *thread1(void *arg);
void *thread2(void *arg);

int main() {
    pthread_t pthread1 = 0;
    pthread_t pthread2 = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&pthread1, NULL, thread1, (void *)0);
    pthread_create(&pthread2, NULL, thread2, (void *)0);

    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);

    return 0;
}

void *thread1(void *arg) {
    int i = 10;
    while (i--) {
        pthread_mutex_lock(&mutex);
        printf("thread1 running\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void *thread2(void *arg) {
    int i = 5;
    while (i--) {
        pthread_mutex_lock(&mutex);
        printf("thread2 running\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}