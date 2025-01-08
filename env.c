#include "shell.h"

/**
 * print_env - print the environment
 *
 * Return: void
 */
void print_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		printf("%s\n", environ[i]);
	}
}
/**
 * _getenv - find the name of a variable
 * @name: the name of the variable
 *
 * Return: char
 */
char *_getenv(const char *name)
{
	int i;
	size_t len = strlen(name);

	for (i =  0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (environ[i] + len + 1);
		}
	}
	return (NULL);
}
