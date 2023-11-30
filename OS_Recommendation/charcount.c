// #include <stdio.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <unistd.h>

// // Shared variables
// int charCount = 0;
// sem_t semaphore;

// // Function to be executed by the thread
// void *countCharacters(void *arg) {
//     while (1) {
//         // Wait for the semaphore to be signaled
//         sem_wait(&semaphore);

//         // Count the characters
//         printf("Thread: Counting characters...\n");
//         printf("Thread: Character count: %d\n", charCount);

//         // Reset the count for the next iteration
//         // charCount = 0;

//         // Signal the semaphore to allow the main thread to input more characters
//         sem_post(&semaphore);

//         // Sleep for a short period to simulate concurrent execution
//         sleep(1);
//     }

//     return NULL;
// }

// int main() {
//     pthread_t tid;
    
//     // Initialize the semaphore
//     sem_init(&semaphore, 0, 1);

//     // Create a thread
//     if (pthread_create(&tid, NULL, countCharacters, NULL) != 0) {
//         fprintf(stderr, "Thread creation failed\n");
//         return 1;
//     }

//     while (1) {
//         // Wait for the semaphore to be signaled
//         sem_wait(&semaphore);

//         // Input a character
//         char inputChar;
//         printf("Main: Enter a character (or 'q' to quit): ");
//         scanf(" %c", &inputChar);

//         // Check if the user wants to quit
//         if (inputChar == 'q') {
//             // Signal the thread to exit
//             sem_post(&semaphore);
//             break;
//         }

//         // Increment the character count
//         charCount++;

//         // Signal the semaphore to allow the thread to count the characters
//         sem_post(&semaphore);
//     }

//     // Wait for the thread to complete
//     pthread_join(tid, NULL);

//     // Destroy the semaphore
//     sem_destroy(&semaphore);

//     return 0;
// }


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define MAX_SIZE 100

sem_t semaphore; // Declare semaphore

void *characterCounter(void *arg) {
    int count = 0;

    while (1) {
        sem_wait(&semaphore); // Wait until the semaphore is available
        printf("Enter a character (or press 'q' to quit): ");
        char input;
        scanf(" %c", &input);

        if (input == 'q') {
            sem_post(&semaphore); // Release the semaphore
            break;
        }

        count++;
        sem_post(&semaphore); // Release the semaphore
    }

    printf("Secondary Thread: Total characters entered: %d\n", count);
    return NULL;
}

int main() {
    pthread_t secondaryThread;
    char inputStr[MAX_SIZE];

    sem_init(&semaphore, 0, 1); // Initialize semaphore

    int threadCreation = pthread_create(&secondaryThread, NULL, characterCounter, NULL);
    if (threadCreation != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    while (1) {
        sem_wait(&semaphore); // Wait until the semaphore is available
        printf("Enter a character (or press 'q' to quit): ");
        scanf(" %c", &inputStr);

        if (inputStr[0] == 'q') {
            sem_post(&semaphore); // Release the semaphore
            break;
        }

        sem_post(&semaphore); // Release the semaphore
    }

    pthread_join(secondaryThread, NULL); // Wait for the secondary thread to finish

    sem_destroy(&semaphore); // Destroy semaphore

    return 0;
}
