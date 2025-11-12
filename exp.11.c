#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function executed by Thread 1
void* task1(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Thread 1: Counting %d\n", i);
        sleep(1); // Simulate work
    }
    return NULL;
}

// Function executed by Thread 2
void* task2(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Thread 2: Counting %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2; // Thread identifiers

    // Create threads
    pthread_create(&t1, NULL, task1, NULL);
    pthread_create(&t2, NULL, task2, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Both threads have finished execution.\n");
    return 0;
}

