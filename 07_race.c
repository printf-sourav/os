// Practical 7: Demonstrate and avoid race condition using mutex
#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t lock;

void* increment_unsafe(void *arg) {
    for (int i = 0; i < 100000; i++)
        counter++;   // Race condition here
    return NULL;
}

void* increment_safe(void *arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);
        counter++;   // Protected by mutex
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    // --- Without mutex (Race Condition) ---
    counter = 0;
    pthread_create(&t1, NULL, increment_unsafe, NULL);
    pthread_create(&t2, NULL, increment_unsafe, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Without mutex (race condition): %d (expected 200000)\n", counter);

    // --- With mutex (No Race Condition) ---
    counter = 0;
    pthread_create(&t1, NULL, increment_safe, NULL);
    pthread_create(&t2, NULL, increment_safe, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("With mutex (no race condition): %d (expected 200000)\n", counter);

    pthread_mutex_destroy(&lock);
    return 0;
}

/*
Compile: gcc 07_race.c -o race -lpthread
Run:     ./race
*/
