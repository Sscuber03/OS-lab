#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

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

        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);  

        execlp("sort", "sort", NULL);

        perror("execlp");
        return 1;
    } else {
        close(pipefd[0]);  

        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);  

        execlp("ls", "ls", NULL);

        perror("execlp");
        wait(NULL);
        return 1;
    }

    return 0;
}
