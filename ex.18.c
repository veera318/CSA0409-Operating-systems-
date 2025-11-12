#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // size of buffer

int buffer[BUFFER_SIZE];
int in = 0, out = 0;  // index variables
sem_t empty, full;    // semaphores
pthread_mutex_t mutex; // mutex lock

void *producer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100;  // produce random item
        sem_wait(&empty);     // wait if buffer full
        pthread_mutex_lock(&mutex); // lock buffer

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);      // signal that buffer has an item
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);      // wait if buffer empty
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);     // signal that buffer has space
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prodThread, consThread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("Producer–Consumer simulation complete.\n");
    return 0;
}

