#include "shell.h"

/*
 * token_input - Tokenize the input
 * @input: The stdin input
 *
 * Return: No return, void function
 */
void token_input(char *input)
{
	char *split = NULL;
	char *tokens[1024] = {NULL};
	int index = 0;

	/* Tokenize the input string using space as a delimiter */
	split = strtok(input, " ");

	while (split)
	{
		/* Check if the token is not an empty string */
		if (strlen(split) > 0)
		{
			/* Store the token in the tokens array */
			tokens[index] = split;
			index += 1;
		}
		/* Get the next token */
		split = strtok(NULL, " ");
	}

	/* If the first token is NULL, return */
	if (tokens[0] == NULL)
	{
		return;
	}

	/* Check for built-in commands */
	if (strcmp(tokens[0], "env") == 0)
	{
		printPrompt();
		return;
	}

	if (strcmp(tokens[0], "exit") == 0 && tokens[1] == NULL)
	{
		/* If the command is 'exit' without arguments, free memory and exit */
		free(tokens[0]);
		exit(0);
	}

	/* Duplicate the first token before modifying it */
	split = strdup(tokens[0]);

	/* Get the full path for the command */
	tokens[0] = _getpath(tokens[0]);

	/* If a valid path is found, free memory and execute the command */
	if (tokens[0] != NULL)
	{
		free(split);
		executable(tokens, input);
		free(tokens[0]);
		return;
	}

	/* If the command is not found, print an error and exit with status 127 */
	fprintf(stderr, "./hsh: 1: %s: not found\n", split);
	free(split);
	exit(127);
}
