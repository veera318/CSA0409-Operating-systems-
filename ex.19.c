#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int shared = 0;               // Shared resource
pthread_mutex_t lock;         // Mutex lock

void* process(void* arg) {
    int i;
    pthread_mutex_lock(&lock); // Entry section (lock)

    printf("\nProcess %d entered critical section.\n", *(int*)arg);
    for (i = 0; i < 5; i++) {
        shared++;
        printf("Process %d incremented shared to %d\n", *(int*)arg, shared);
        sleep(1);  // Simulate work
    }

    printf("Process %d leaving critical section.\n", *(int*)arg);
    pthread_mutex_unlock(&lock); // Exit section (unlock)

    return NULL;
}

int main() {
    pthread_t t1, t2;
    int p1 = 1, p2 = 2;

    // Initialize the mutex lock
    pthread_mutex_init(&lock, NULL);

    // Create two threads (processes)
    pthread_create(&t1, NULL, process, &p1);
    pthread_create(&t2, NULL, process, &p2);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    printf("\nFinal value of shared resource = %d\n", shared);
    return 0;
}

