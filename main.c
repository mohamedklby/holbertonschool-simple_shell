#include "shell.h"

/**
 * main - Point d'entrée du programme
 *
 * Retour: 0 pour indiquer un succès
 */

int main(void)
{
	/* Déclare un pointeur de type char pour stocker l'entrée utilisateur (initialisé à NULL) */
	char *input = NULL;

	/* Déclare une variable de type size_t pour stocker la longueur de l'entrée (initialisée à 0) */
	size_t len_input = 0;

	/* Déclare une variable de type ssize_t pour stocker le nombre de caractères lus */
	ssize_t read = 0;

	/* Boucle infinie pour continuer à demander l'entrée de l'utilisateur */
	while (1)
	{
		/* Vérifie si l'entrée provient d'un terminal interactif (c'est-à-dire un shell) */
		if (isatty(STDIN_FILENO))  
		{
			/* Affiche l'invite de commande "SimpleSimple$" */
			printf("SimpleSimple$ ");

			/* Force l'affichage immédiat de l'invite de commande (utile pour s'assurer que l'invite apparaisse) */
			fflush(stdout);            
		}

		/* Utilise getline pour lire une ligne de l'entrée standard (stdin) */
		read = getline(&input, &len_input, stdin);

		/* Si l'entrée de l'utilisateur est un EOF (fin de fichier, comme avec Ctrl+D) */
		if (read == EOF)
		{
			/* Libère la mémoire allouée à 'input' */
			free(input);

			/* Quitte le programme avec le statut 0, indiquant une sortie propre */
			exit(0);                 
		}

		/* Si la lecture a réussi et si le dernier caractère est un saut de ligne (\n) */
		if (read > 0 && input[read - 1] == '\n')
		{
			/* Remplace le saut de ligne par un caractère de fin de chaîne '\0' */
			input[read - 1] = '\0';  
		}

		/* Appelle la fonction `token_input` pour traiter et analyser l'entrée de l'utilisateur */
		token_input(input);
	}

	/* Libère la mémoire allouée à 'input' une fois la boucle terminée */
	free(input);                   

	/* Retourne 0 pour indiquer une exécution réussie du programme */
	return (0);                     
}

