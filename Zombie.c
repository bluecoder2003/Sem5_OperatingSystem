#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid == 0) {
        // Child process
        printf("Child process with PID: %d is running\n", getpid());
        // Exit the child process
        // No wait() or exit() called here, creating a zombie process
    } else if (pid > 0) {
        // Parent process
        printf("Parent process with PID: %d created child with PID: %d\n", getpid(), pid);
        // Wait for the child process to become a zombie
        wait(NULL);
        printf("Zombie process with PID: %d has been cleaned up\n", pid);
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}
