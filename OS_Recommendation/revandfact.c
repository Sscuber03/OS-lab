#include <stdio.h>
#include <pthread.h>

// Structure to pass data to threads
struct ThreadData {
    int number;
    int result;  // To store the result
};

// Function to calculate factorial
void *calculateFactorial(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    int n = data->number;
    int factorial = 1;

    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }

    // Store the result in the structure
    data->result = factorial;

    // Exit the thread
    pthread_exit(NULL);
}

// Function to reverse a number
void *reverseNumber(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    int n = data->number;
    int reversed = 0;

    while (n != 0) {
        reversed = (reversed * 10) + (n % 10);
        n /= 10;
        // printf("%d\n", reversed);
    }

    // Store the result in the structure
    data->result = reversed;

    // Exit the thread
    pthread_exit(NULL);
}

int main() {
    pthread_t factorialThread, reverseThread;
    struct ThreadData factorialData, reverseData;

    // Input a number from the user
    printf("Enter a number: ");
    scanf("%d", &factorialData.number);
    reverseData.number = factorialData.number;

    // Create threads
    pthread_create(&factorialThread, NULL, calculateFactorial, (void *)&factorialData);
    pthread_create(&reverseThread, NULL, reverseNumber, (void *)&reverseData);

    // Wait for threads to finish
    pthread_join(factorialThread, NULL);
    pthread_join(reverseThread, NULL);

    // Display results
    printf("Factorial: %d\n", factorialData.result);
    printf("Reversed Number: %d\n", reverseData.result);

    return 0;
}
