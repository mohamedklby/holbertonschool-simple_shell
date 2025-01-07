#include "shell.h"

/**
 * getPath - search for the file in the PATH
 * @file: the file to search for in the PATH
 * Description: search for the and send the absolute path to the file if found
 * Return: the file path if found, or NULL
 */
char *getPath(char *file)
{
	char *path = NULL; /* to store the path */
	char *file_path = NULL; /* to store the file path */
	char *path_env = NULL; /* to store the env PATH */
	/* struct stat to store the file info */
	struct stat file_info;
	int i; /* index for loop */

	for (i = 0; file[i] != '\0'; i++) /* loop to go through the file name */
	{
		if (file[i] == '/' || file[i] == '.') /* if contains '/' or '.' = PATH */
		{
			if (stat(file, &file_info) == 0) /* check if file exists */
				return (strdup(file)); /* return a copy of the file */
			return (NULL); /* or return NULL if not found */
		}
	}
	path = getEnv("PATH"); /* get the PATH environ variable */
	if (!path) /* if getEnv fails or path is NULL */
		return (NULL);
	path_env = strdup(path); /* duplicate the PATH env variable and store it */
	if (path_env == NULL) /* if strdup (duplicate) fails */
		return (NULL);
	path = strtok(path_env, ":"); /* split the PATH env variable using ':' */
	while (path) /* loop through the PATH as long as it's not NULL */
	{
		/* allocate memory for the file path */
		/* size of the path + size of the file + '/' + '\0' */
		file_path = malloc(sizeof(char) * (strlen(path) + strlen(file) + 2));
		/* if malloc fails to allocate memory, return NULL*/
		if (file_path == NULL)
		{
			perror("Error: malloc failed");
			return (NULL);
		}
		/* concatenate the path with the file name using sprintf and / to separate */
		sprintf(file_path, "%s/%s", path, file);
		if (file_path != NULL && stat(file_path, &file_info) == 0)
		{
			free(path_env); /* if file exists or file_path is NULL free path_env */
			return (file_path); /* return the file path */
		}
		path = strtok(NULL, ":"); /* get the next path */
		free(file_path); /* free the file path if file not found */
	}
	free(path_env); /* free the path_env */
	return (NULL); /* return NULL if file not found */
}
