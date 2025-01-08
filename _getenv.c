#include "shell.h"
/**
 * print_env - print the current environment variables
 *
 * Return: 0 if successeful, otherwise 1
 */
void print_env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
/**
 * _getenv - function to get the environement variable
 * @name: name of the environment variable
 *
 * Return: 0 if successful, otherwise 1
 */
char *_getenv(const char *name)
{
	int i;
	size_t len = strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (environ[i] + len + 1);
		}
	}
	return (NULL);
}
