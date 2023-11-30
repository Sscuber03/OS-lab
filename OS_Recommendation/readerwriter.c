// #include <stdio.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <unistd.h>

// #define BUFFER_SIZE 5

// int buffer[BUFFER_SIZE];
// int in = 0, out = 0;

// sem_t mutex, full, empty;

// void *reader(void *arg) {
//     int item = 1;

//     while (1) {
//         // Wait if the buffer is empty
//         sem_wait(&full);
//         // Wait for mutex to access the critical section
//         sem_wait(&mutex);

//         // Consume item from the buffer
//         int item = buffer[out];
//         printf("Consumed: %d\n", item);
//         out = (out + 1) % BUFFER_SIZE;

//         // Signal mutex and empty
//         sem_post(&mutex);
//         sem_post(&empty);

//         sleep(1);  // Sleep to simulate time taken to consume an item
//     }

//     return NULL;
// }

// void *writer(void *arg) {
//     int item = 1;

//     while (1) {
//         // Wait if the buffer is full
//         sem_wait(&empty);
//         // Wait for mutex to access the critical section
//         sem_wait(&mutex);

//         // Produce item and add to the buffer
//         buffer[in] = item;
//         printf("Produced: %d\n", item);
//         in = (in + 1) % BUFFER_SIZE;

//         // Signal mutex and full
//         sem_post(&mutex);
//         sem_post(&full);

//         item++;
//         sleep(1);  // Sleep to simulate time taken to produce an item
//     }

//     return NULL;
// }

// int main() {
//     // Initialize semaphores
//     sem_init(&mutex, 0, 1);
//     sem_init(&full, 0, 0);
//     sem_init(&empty, 0, BUFFER_SIZE);

//     // Create threads
//     pthread_t tid1, tid2;
//     pthread_create(&tid1, NULL, reader, NULL);
//     pthread_create(&tid2, NULL, writer, NULL);

//     // Wait for threads to complete
//     pthread_join(tid1, NULL);
//     pthread_join(tid2, NULL);

//     // Destroy semaphores
//     sem_destroy(&mutex);
//     sem_destroy(&full);
//     sem_destroy(&empty);

//     return 0;
// }

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS_COUNT 3
#define WRITERS_COUNT 2

sem_t mutex, wrt;
int readCount = 0;

void *reader(void *arg) {
    while (1) {
        // Wait for permission to enter the critical section
        sem_wait(&mutex);

        // Increment the number of readers
        readCount++;

        // If it's the first reader, wait for permission from writers
        if (readCount == 1) {
            sem_wait(&wrt);
        }

        // Release the mutex to allow other readers
        sem_post(&mutex);

        // Read from the resource
        printf("Reader %d reading...\n", (int)arg);
        sleep(1);  // Simulate reading time

        // Reacquire the mutex to update the reader count
        sem_wait(&mutex);
        readCount--;

        // If it's the last reader, signal writers to access the resource
        if (readCount == 0) {
            sem_post(&wrt);
        }

        // Release the mutex
        sem_post(&mutex);

        sleep(2);  // Sleep to simulate time between consecutive reads
    }

    return NULL;
}

void *writer(void *arg) {
    while (1) {
        // Wait for permission to write to the resource
        sem_wait(&wrt);

        // Write to the resource
        printf("Writer %d writing...\n", (int)arg);
        sleep(2);  // Simulate writing time

        // Release the permission for other writers or readers
        sem_post(&wrt);

        sleep(3);  // Sleep to simulate time between consecutive writes
    }

    return NULL;
}

int main() {
    pthread_t readers[READERS_COUNT], writers[WRITERS_COUNT];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader and writer threads
    for (int i = 0; i < READERS_COUNT; ++i) {
        pthread_create(&readers[i], NULL, reader, (void *)(intptr_t)i);
    }

    for (int i = 0; i < WRITERS_COUNT; ++i) {
        pthread_create(&writers[i], NULL, writer, (void *)(intptr_t)i);
    }

    // Sleep for a while to allow reader and writer threads to run
    sleep(20);

    // Terminate the threads
    for (int i = 0; i < READERS_COUNT; ++i) {
        pthread_cancel(readers[i]);
    }

    for (int i = 0; i < WRITERS_COUNT; ++i) {
        pthread_cancel(writers[i]);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
