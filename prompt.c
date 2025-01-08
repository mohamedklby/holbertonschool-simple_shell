#include "shell.h"

/**
 * printPrompt - Print the environment variables.
 * This function prints the environment variables to the standard output.
 * Each environment variable is printed on a new line.
 * Return: no return, void function
 */

void printPrompt(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}
