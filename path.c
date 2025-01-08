
#include "shell.h"

/**
 * is_a_command - Checks if the input corresponds to an executable command
 * by using the PATH environment variable and the access function.
 *
 * @args: The command to check, provided as a string.
 *
 * Return: NULL if the command is not found or an error occurs.
 * Otherwise, returns the full path to the executable.
 */
char *is_a_command(char *args)
{
	char *path, *tmp, *directory, *executable_path;
	struct stat st;

	if (access(args, X_OK) == 0)
		return (strdup(args));

	path = _getenv("PATH");
	if (!path)
		return (0);


	tmp = strdup(path);
	if (!tmp)
		return (0);

	executable_path = malloc(4096);
	if (!executable_path)
	{
		free(tmp);
		return (0);
	}


	directory = strtok(tmp, ":");
	while (directory)
	{
		sprintf(executable_path, "%s/%s", directory, args);

		if (stat(executable_path, &st) == 0 && access(executable_path, X_OK) == 0)
		{
			free(tmp);
			return (executable_path);
		}
		directory = strtok(NULL, ":");
	}

	free(executable_path);
	free(tmp);
	return (0);
}
