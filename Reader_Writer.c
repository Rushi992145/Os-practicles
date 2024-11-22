#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define R 5 // Number of Readers
#define W 5 // Number of Writers

int readcount = 0;
pthread_mutex_t x;
sem_t wsem;
int shared_resource = 5;

// Function prototypes
void *reader(void *a);
void *writer(void *a);

int main() {
    int i;
    pthread_t thread_read[R], thread_write[W];

    // Initialize mutex and semaphore
    pthread_mutex_init(&x, NULL);
    sem_init(&wsem, 0, 1);

    printf("Readers have priority:\n");

    // Create writer threads
    for (i = 0; i < W; i++) 
        pthread_create(&thread_write[i], NULL, writer, (void *)(intptr_t)i);

    // Create reader threads
    for (i = 0; i < R; i++) 
        pthread_create(&thread_read[i], NULL, reader, (void *)(intptr_t)i);

    // Wait for writer threads to complete
    for (i = 0; i < W; i++) 
        pthread_join(thread_write[i], NULL);

    // Wait for reader threads to complete
    for (i = 0; i < R; i++) 
        pthread_join(thread_read[i], NULL);

    // Destroy mutex and semaphore
    // pthread_mutex_destroy(&x);
    // sem_destroy(&wsem);

    return 0;
}

void *reader(void *a) {
    int r = (intptr_t)a;
    int i = 0;

    while (i < 5) {
        pthread_mutex_lock(&x);
        readcount++;
        if (readcount == 1)
            sem_wait(&wsem); // First reader locks the semaphore
        pthread_mutex_unlock(&x);

        // Reading the shared resource
        printf("\t\tReader %d is reading: %d\n", r, shared_resource);

        pthread_mutex_lock(&x);
        readcount--;
        if (readcount == 0)
            sem_post(&wsem); // Last reader unlocks the semaphore
        pthread_mutex_unlock(&x);

        sleep(rand() % 3); // Simulate reading time
        i++;
    }
    return NULL;
}

void *writer(void *a) {
    int w = (intptr_t)a;
    int i = 0;

    while (i < 2) {
        sem_wait(&wsem); // Writer locks the semaphore

        // Writing to the shared resource
        shared_resource += 5;
        printf("Writer %d is writing: %d\n", w, shared_resource);

        sem_post(&wsem); // Writer unlocks the semaphore

        sleep(rand() % 3); // Simulate writing time
        i++;
    }
    return NULL;
}
