#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) { 
        char *args[] = {"ls", NULL}; 
        if (execvp(args[0], args) == -1) { 
            perror("execvp");
            return 1;
        }
    } else {
        wait(NULL);
        printf("Child process completed.\n");
    }

    return 0;
}
