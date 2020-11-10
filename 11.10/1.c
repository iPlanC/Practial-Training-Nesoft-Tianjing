#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *thread1(void *arg);
void *thread2(void *arg);

int main() {
    pthread_t pthread1 = 0;
    pthread_t pthread2 = 0;
    if (pthread_create(&pthread1, NULL, thread1, (void *)10) == 0) {
        if (pthread_create(&pthread2, NULL, thread2, (void *)10) == 0) {
            while (1);
        }
    }
    return 0;
}

void *thread1(void *arg) {
    int i = *(int *)arg;
    while (i--) {
        printf("Hello ");
        sleep(1);
    }
    return NULL;
}

void *thread2(void *arg) {
    int i = *(int *)arg;
    while (i--) {
        printf("World\n");
        sleep(1);
    }
    return NULL;
}
