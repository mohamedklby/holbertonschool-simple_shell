#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - The main function of the simple shell
 * Return: 0 on success, -1 on error
 */
int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;

	while (1)
	{
		/* Display the prompt */
		printf("#cisfun$ ");
		fflush(stdout);

		/* Read the command from the user */
		nread = getline(&command, &len, stdin);

		if (nread == -1) /* Handle EOF (Ctrl+D) */
		{
			if (feof(stdin))
			{
				printf("\n");
				free(command);
				exit(0);
			}
			else
			{
				perror("getline");
				free(command);
				exit(1);
			}
		}

		/* Remove the trailing newline character */
		command[nread - 1] = '\0';

		/* Create a child process to execute the command */
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			free(command);
			exit(1);
		}

		if (pid == 0)
		{
			/* Child process - execute the command using execve */
			if (execve(command, (char *[]){command, NULL}, NULL) == -1)
			{
				perror("./shell");
			}
			free(command);
			exit(1);
		}
		else
		{
			/* Parent process - wait for the child to finish */
			waitpid(pid, &status, 0);
		}
	}

	free(command);
	return (0);
}

