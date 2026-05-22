#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t empty, full;

int buffer[5];
int in = 0, out = 0;

pthread_mutex_t mutex;

void *producer(){

    for(int i = 1; i <= 5; i++){

        sem_wait(&empty);

        pthread_mutex_lock(&mutex);

        buffer[in] = i;

        printf("Produced %d\n", i);

        in = (in + 1) % 5;

        pthread_mutex_unlock(&mutex);

        sem_post(&full);
    }
}

void *consumer(){

    for(int i = 1; i <= 5; i++){

        sem_wait(&full);

        pthread_mutex_lock(&mutex);

        printf("Consumed %d\n", buffer[out]);

        out = (out + 1) % 5;

        pthread_mutex_unlock(&mutex);

        sem_post(&empty);
    }
}

int main(){

    pthread_t t1, t2;

    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}