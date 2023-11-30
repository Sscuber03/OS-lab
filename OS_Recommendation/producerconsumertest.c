#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t mutex, full, empty;

void *producer(void *arg) {
    int item = 1;

    while (1) {
        // Wait if the buffer is full
        sem_wait(&empty);
        // Wait for mutex to access the critical section
        sem_wait(&mutex);

        // Produce item and add to the buffer
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        // Signal mutex and full
        sem_post(&mutex);
        sem_post(&full);

        item++;
        sleep(1);  // Sleep to simulate time taken to produce an item
    }

    return NULL;
}

void *consumer(void *arg) {
    while (1) {
        // Wait if the buffer is empty
        sem_wait(&full);
        // Wait for mutex to access the critical section
        sem_wait(&mutex);

        // Consume item from the buffer
        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        // Signal mutex and empty
        sem_post(&mutex);
        sem_post(&empty);

        sleep(1);  // Sleep to simulate time taken to consume an item
    }

    return NULL;
}

int main() {
    pthread_t producerThread, consumerThread;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Sleep for a while to allow producer and consumer threads to run
    sleep(10);

    // Terminate the threads
    pthread_cancel(producerThread);
    pthread_cancel(consumerThread);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
