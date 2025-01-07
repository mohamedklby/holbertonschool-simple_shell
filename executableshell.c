#include "shell.h"

/*
 * executable - Execute a file if it has executable permissions
 *
 * @argv: Path to the executable file
 * @input: Input put by the user of this shell
 * Return: No return value (void function)
 */
void executable(char *argv[], char *input)
{
	int status;
	int status_exit;
	pid_t child;

	/* Check if the file has executable permissions */
	if (access(argv[0], X_OK) != 0)
	{
		/* Print an error message and exit if the file is not executable */
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		free(argv[0]);
		exit(127);
	}

	/* Fork a child process */
	child = fork();

	if (child == -1)
	{
		/* Handle fork failure */
		perror("Fail Fork\n");
		exit(0);
	}
	else if (child == 0)
	{
		/* Child process: execute the specified program */
		execve(argv[0], argv, environ);
		free(argv[0]);
		exit(0);
	}
	else
	{
		/* Parent process: wait for the child to finish */
		wait(&status);

		/* Check if the child process exited normally */
		if (WIFEXITED(status))
		{
			/* Get the exit status of the child process */
			status_exit = WEXITSTATUS(status);

			/* If the exit status is not 0, free memory and exit with status 2 */
			if (status_exit != 0)
			{
				free(argv[0]);
				free(input);
				exit(2);
			}
		}
	}
}
