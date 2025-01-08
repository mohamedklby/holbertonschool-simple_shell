#include "main.h"

/**
 * _getpath- function that finds the path to execute command
 *
 * @command: command enter by user in input
 *
 * Return: command if command has '/', result of concat with PATH
 * or NULL if nothing is found
 */

char *_getpath(char *command)
{
	int i = 0;
	char *token = NULL;
	char *cache;
	char *result = NULL;

	if (strchr(command, '/') != NULL)
		return (strdup(command));
	while (environ[i])
	{
		cache = strdup(environ[i]);
		token = strtok(cache, "=");
		if (strcmp(token, "PATH") == 0)
		{
			token = strtok(NULL, "=");
			token = strtok(token, ":");
			while (token)
			{
				result = malloc(strlen(token) + strlen(command) + 2);
				if (result ==  NULL)
				{
					perror("Malloc is NULL");
					return (NULL);
				}
				sprintf(result, "%s/%s", token, command);
				if (access(result, X_OK) == 0)
				{
					free(cache);
					return (result);
				}
				free(result);
				token = strtok(NULL, ":");
			}
		}
		free(cache);
		i++;
	}
	free(command);
	return (NULL);
}
