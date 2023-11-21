#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        char *argv[] = {"./sequential_min_max", "3", "3", NULL};
        
         if (execv("./sequential_min_max", argv) == -1) {
            perror("execv");
            exit(EXIT_FAILURE);
        }

        fprintf(stderr, "Ошибка: execv не выполнен\n");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Дочерний процесс успешно завершил выполнение с кодом: %d\n", WEXITSTATUS(status));
        } else {
            printf("Дочерний процесс завершил выполнение с ошибкой\n");
        }
    }

    return 0;
}
