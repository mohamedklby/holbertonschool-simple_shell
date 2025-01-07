#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT 1024

/**
 * main - Simple shell program
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *command;
	pid_t pid;
	int status;

	while (1)
	{
		// Display prompt
		printf("#cisfun$ ");

		// Get user input
		nread = getline(&line, &len, stdin);

		// Check for EOF (Ctrl+D)
		if (nread == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break; // End of file, exit the shell
			}
			else
			{
				perror("getline");
				continue;
			}
		}

		// Remove newline character at the end of input
		if (line[nread - 1] == '\n')
		{
			line[nread - 1] = '\0';
		}

		// Parse the command (only a single word is allowed)
		command = strtok(line, " \t");

		if (command == NULL) // Empty line, continue
			continue;

		// Fork a child process to execute the command
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		else if (pid == 0)
		{
			// Child process: attempt to execute the command
			if (execve(command, &command, NULL) == -1)
			{
				// If command is not found, print error message
				perror("./shell");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			// Parent process: wait for the child to finish
			waitpid(pid, &status, 0);
		}
	}


