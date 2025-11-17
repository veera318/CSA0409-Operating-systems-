#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Thread function
void* threadFunction(void* arg) {
    printf("Thread started using pthread_create().\n");

    // Demonstrate pthread_equal()
    pthread_t current = pthread_self();
    pthread_t passed = *(pthread_t*)arg;

    if (pthread_equal(current, passed))
        printf("pthread_equal(): Thread IDs are equal.\n");
    else
        printf("pthread_equal(): Thread IDs are NOT equal.\n");

    printf("Thread is now calling pthread_exit().\n");
    pthread_exit(NULL);  // Thread terminates here
}

int main() {
    pthread_t tid;

    // ------------ CREATE THREAD -------------
    if (pthread_create(&tid, NULL, threadFunction, &tid) == 0)
        printf("pthread_create(): Thread created successfully.\n");
    else {
        printf("Error creating thread.\n");
        return 1;
    }

    // ------------ JOIN THREAD -------------
    printf("Main thread waiting using pthread_join().\n");
    pthread_join(tid, NULL);

    printf("pthread_join(): Thread has finished execution.\n");
    printf("All thread operations demonstrated successfully.\n");

    return 0;
}

