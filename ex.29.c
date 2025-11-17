#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;     // Counts empty slots
sem_t full;      // Counts filled slots
pthread_mutex_t mutex;   // Mutual exclusion

void* producer(void* p) {
    int item = 1;
    while (1) {
        sleep(1);  // Simulate production time

        sem_wait(&empty);          // Wait for empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        buffer[in] = item;
        printf("Producer produced: %d at buffer[%d]\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        item++;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full);              // Increase count of full slots
    }
}

void* consumer(void* c) {
    while (1) {
        sleep(2);  // Simulate consumption time

        sem_wait(&full);           // Wait for full slot
        pthread_mutex_lock(&mutex); // Enter critical section

        int item = buffer[out];
        printf("Consumer consumed: %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty);             // Increase count of empty slots
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE); // Buffer has 5 empty slots
    sem_init(&full, 0, 0);            // Initially no full slots
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}

