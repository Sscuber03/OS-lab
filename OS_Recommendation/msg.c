#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {

        close(pipefd[1]); 

        char message[100];
        read(pipefd[0], message, sizeof(message));
        printf("Child received message from parent: %s\n", message);

        close(pipefd[0]);
    } else {
 
        close(pipefd[0]);  

        char message[] = "Hello from Sambit!";

        write(pipefd[1], message, strlen(message) + 1);

        close(pipefd[1]); 
    }

    return 0;
}
