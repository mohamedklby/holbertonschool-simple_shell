#include "shell.h"

/*
 * executable - Exécute un fichier s'il a les permissions d'exécution
 *
 * @argv: Chemin vers le fichier exécutable
 * @input: Entrée fournie par l'utilisateur de ce shell
 * Retour: Pas de valeur de retour (fonction void)
 */
void executable(char *argv[], char *input)
{
	int status;
	int status_exit;
	pid_t child;

	/* Vérifie si le fichier a des permissions d'exécution */
	if (access(argv[0], X_OK) != 0)
	{
		/* Affiche un message d'erreur et quitte si le fichier n'est pas exécutable */
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		free(argv[0]);
		exit(127);
	}

	/* Crée un processus fils */
	child = fork();

	if (child == -1)
	{
		/* Gère l'échec de fork */
		perror("Échec du fork\n");
		exit(0);
	}
	else if (child == 0)
	{
		/* Processus fils : exécute le programme spécifié */
		execve(argv[0], argv, environ);
		free(argv[0]);
		exit(0);
	}
	else
	{
		/* Processus parent : attend la fin du processus fils */
		wait(&status);

		/* Vérifie si le processus fils s'est terminé normalement */
		if (WIFEXITED(status))
		{
			/* Récupère le statut de sortie du processus fils */
			status_exit = WEXITSTATUS(status);

			/* Si le statut de sortie n'est pas 0, libère la mémoire et quitte avec le statut 2 */
			if (status_exit != 0)
			{
				free(argv[0]);
				free(input);
				exit(2);
			}
		}
	}
}

