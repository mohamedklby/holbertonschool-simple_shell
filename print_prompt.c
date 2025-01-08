#include "shell.h"

/**
 * print_prompt - prints the prompt
 *
 * Return: void
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO) == 1)
	{
		printf("$ ");
		fflush(stdout);
	}
}
