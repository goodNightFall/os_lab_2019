#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        printf("Child process is running\n");
        sleep(3);
        printf("Child process is done\n");
        exit(0); 
    } else if (child_pid > 0) {
        printf("Parent process is waiting for the child...\n");
        wait(NULL);
        printf("Parent process is done\n");
    } else {
        perror("fork");
        return 1; 
    }

    return 0;
}
