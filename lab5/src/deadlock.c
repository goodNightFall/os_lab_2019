#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Мьютексы для блокировки ресурсов
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *thread_function1(void *arg) {
    pthread_mutex_lock(&mutex1);
    printf("pnum 1: mutex1\n");

    sleep(2);

    pthread_mutex_lock(&mutex2);
    printf("pnum 1: mutex2\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    pthread_exit(NULL);
}

void *thread_function2(void *arg) {
    pthread_mutex_lock(&mutex2);
    printf("pnum 2: mutex2\n");

    sleep(2);

    pthread_mutex_lock(&mutex1);
    printf("pnum 2: mutex1\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_function1, NULL);
    pthread_create(&thread2, NULL, thread_function2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}