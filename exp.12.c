#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS]; // One mutex per fork

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < 3; i++) { // Each philosopher eats 3 times
        printf("Philosopher %d is thinking ??\n", id + 1);
        sleep(1);

        // Pick up forks
        printf("Philosopher %d is hungry ???\n", id + 1);
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        // Eating
        printf("Philosopher %d is eating ??\n", id + 1);
        sleep(2);

        // Put down forks
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
        printf("Philosopher %d finished eating and put down forks ??\n", id + 1);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutexes (forks)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_mutex_init(&forks[i], NULL);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_mutex_destroy(&forks[i]);

    printf("\nAll philosophers have finished dining.\n");
    return 0;
}

