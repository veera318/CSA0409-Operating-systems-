#include <stdio.h>
#include <unistd.h>   // For fork(), getpid(), getppid()
#include <sys/types.h> // For pid_t
#include <stdlib.h>    // For exit()

int main() {
    pid_t pid;

    // Create a new process using fork()
    pid = fork();

    if (pid < 0) {
        // Error occurred during fork
        perror("Fork failed");  // Will print a more detailed error message
        exit(1);  // Exit the program with an error code 1
    }

    if (pid == 0) {
        // Child process
        printf("Child Process\n");
        printf("Current Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
    } else {
        // Parent process
        printf("Parent Process\n");
        printf("Current Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
    }

    return 0;
}

