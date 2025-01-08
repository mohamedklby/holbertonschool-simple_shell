#include "shell.h"
#include <stdio.h>
#include <unistd.h>

/**
 * execute_args - Execute a command and its arguments in a separate process.
 * @args: Array of strings containing the command and arguments to execute.
 *
 * Return: 0 on success, -1 or 127 on failure.
 */
int execute_args(char **args)
{
	int status;
	char *path;
	pid_t pid;

	if (!args[0])
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (0);

	path = is_a_command(args[0]);

	if (!path)
	{
		fprintf(stderr, "hsh %s: Error&\n", args[0]);
		return (127);
	}
	pid = fork();

	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
			perror("hsh");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("hsh");
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(path);

	return (0);
}
