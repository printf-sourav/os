// Practical 9: Producer-Consumer with semaphores (satisfies all 3 critical section requirements)
// Mutual Exclusion, Progress, Bounded Waiting — all satisfied via semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;   // counts empty slots
sem_t full;    // counts filled slots
pthread_mutex_t mutex;

void* producer(void *arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&empty);             // wait if buffer is full
        pthread_mutex_lock(&mutex);   // enter critical section

        buffer[in] = i;
        printf("Produced: %d at slot %d\n", i, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // exit critical section
        sem_post(&full);              // signal item available
    }
    return NULL;
}

void* consumer(void *arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&full);              // wait if buffer is empty
        pthread_mutex_lock(&mutex);   // enter critical section

        int item = buffer[out];
        printf("Consumed: %d from slot %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // exit critical section
        sem_post(&empty);             // signal slot is free
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full,  0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}

/*
Compile: gcc 09_producer_consumer.c -o prodcon -lpthread
Run:     ./prodcon
*/
