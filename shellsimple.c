#include "shell.h"

/**
 * main - entry point of the program
 * Description: run the shell program
 * Only if stdin is associated with a terminal
 * Print the prompt, get the input, parse the input line, execute the command
 * Return: 0 on success or a number on failure
 */
int main(void) {
    char *input_line = NULL;
    char **command_arguments = NULL;
    size_t len = 0;
    ssize_t read;
	int exit_status;

    while (1) {
        if (isatty(STDIN_FILENO)) {
            printPrompt();
            fflush(stdout);
        }

        read = getline(&input_line, &len, stdin);

        if (read == EOF) {
            free(input_line);
            exit(0); /* Exit with status 0 for EOF */
        }

        command_arguments = parseLine(input_line);

        if (strcmp(command_arguments[0], "exit") == 0) {
            freeDP(command_arguments);
            free(input_line);
            exit(0);
        }

        if (emptyLine(input_line) == 1)
            continue;

        exit_status = execute(command_arguments);

        if (exit_status == 127) {
            free(input_line);
            freeDP(command_arguments);
            exit(127);	/* Handle the case of a wrong command here */
        } else if (exit_status == -1) {
            /* Handle other execution errors if needed */
            free(input_line);
            freeDP(command_arguments);
            exit(2); /* Exit with status 2 for other execution errors */
        }
        
        freeDP(command_arguments);
    }

    free(input_line);
    return 0;
}
