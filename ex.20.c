#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;               // Semaphore to control access for writers
pthread_mutex_t mutex;   // Mutex to protect reader count
int readcount = 0;       // Number of readers currently reading
int data = 0;            // Shared resource (example data)

void *writer(void *wno) {
    int w = *(int *)wno;
    while (1) {
        sem_wait(&wrt); // Writer gets exclusive access
        data++;
        printf("Writer %d is writing... Data = %d\n", w, data);
        sleep(1);
        sem_post(&wrt); // Release write lock
        sleep(1);
    }
}

void *reader(void *rno) {
    int r = *(int *)rno;
    while (1) {
        pthread_mutex_lock(&mutex);
        readcount++;
        if (readcount == 1)
            sem_wait(&wrt); // First reader locks writer
        pthread_mutex_unlock(&mutex);

        printf("Reader %d is reading... Data = %d\n", r, data);
        sleep(1);

        pthread_mutex_lock(&mutex);
        readcount--;
        if (readcount == 0)
            sem_post(&wrt); // Last reader releases writer
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}

int main() {
    pthread_t rtid[5], wtid[3];
    int rno[5] = {1, 2, 3, 4, 5};
    int wno[3] = {1, 2, 3};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Create reader threads
    for (int i = 0; i < 5; i++)
        pthread_create(&rtid[i], NULL, reader, &rno[i]);

    // Create writer threads
    for (int i = 0; i < 3; i++)
        pthread_create(&wtid[i], NULL, writer, &wno[i]);

    // Wait (never ends in this simulation)
    for (int i = 0; i < 5; i++)
        pthread_join(rtid[i], NULL);
    for (int i = 0; i < 3; i++)
        pthread_join(wtid[i], NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}

