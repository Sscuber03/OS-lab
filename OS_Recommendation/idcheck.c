#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *threadFunction(void *arg) {
    printf("Thread ID: %lu\n", pthread_self()); 
    printf("Process ID: %d\n", getpid());
    return NULL;
}

int main() {
    pthread_t tid;

    if (pthread_create(&tid, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Thread creation failed\n");
        return 1;
    }

    printf("Main Thread ID: %lu\n", pthread_self());  
    printf("Process ID: %d\n", getpid()); 

    pthread_join(tid, NULL);

    return 0;
}
