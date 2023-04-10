#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64

// Function to read input from the user
void read_input(char *input) {
    printf(">> ");
    fgets(input, MAX_COMMAND_LENGTH, stdin);
}

// Function to parse input into command and arguments
void parse_input(char *input, char **command, char **arguments) {
    char *token = strtok(input, " \n");
    *command = token;
    int i = 0;
    while (token != NULL) {
        arguments[i++] = token;
        token = strtok(NULL, " \n");
    }
    arguments[i] = NULL;
}

int main() {
    char input[MAX_COMMAND_LENGTH];
    char *command;
    char *arguments[MAX_ARGUMENTS];

    while (1) {
        read_input(input);
        parse_input(input, &command, arguments);

        // Fork a child process
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // Child process: execute the command
            execvp(command, arguments);
            perror("execvp");
            exit(1);
        } else {
            // Parent process: wait for child to complete (if not a background process)
            int status;
            if (strcmp(arguments[0], "&") != 0) {
                waitpid(pid, &status, 0);
            }
        }
    }

    return 0;
}
