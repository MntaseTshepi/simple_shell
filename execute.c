#include "shell.h"

void execute_external_command(char *command, char **argv) {
    pid_t pid;
    int status;
    char *full_path;
    char *errorMessage = "Command not found\n";

    full_path = getCommandPath(command);

    if (full_path == NULL) {
       write(STDERR_FILENO, errorMessage, _strlen(errorMessage));
        return;
    }

    if (access(full_path, X_OK) != 0) {
        perror(command);
        free(full_path);
        return;
    }

    if ((pid = fork()) == -1) {
        perror(command);
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execve(full_path, argv, NULL) == -1) {
            perror(command);
            exit(EXIT_FAILURE);
        }
    } else {
        if (waitpid(pid, &status, 0) == -1) {
            perror(command);
            exit(EXIT_FAILURE);
        }
    }

    free(full_path);
}

