#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i;
    int num_children = 3; // Number of child processes to create

    printf("Process 1, PID= %d\n", getpid());

    // Loop to create child processes
    for (i = 0; i < num_children; i++) {
        pid = fork(); // Create a new process

        if (pid < 0) {
            // Error handling
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process code
            printf("Child %d created, running with PID: %d, Parent PID: %d\n", i + 1, getpid(), getppid());
            exit(EXIT_SUCCESS); // Child must exit to avoid further forking
        }
        // Parent process continues the loop to fork the next child
    }

    // Parent process waits for all children to terminate
    for (i = 0; i < num_children; i++) {
        wait(NULL); // Wait for any child process to terminate
    }

    printf("All children have exited. Parent process (PID: %d) exiting.\n", getpid());
    return 0;
}