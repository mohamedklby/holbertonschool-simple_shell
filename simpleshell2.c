#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		nread = getline(&command, &len, stdin);
		if (nread == -1)
		{
			free(command);
			exit(0);
		}

		command[nread - 1] = '\0'; // Remove newline

		pid = fork();
		if (pid == 0)
		{
			if (execve(command, (char *[]){command, NULL}, NULL) == -1)
				perror("Error");
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}

	free(command);
	return 0;
}

