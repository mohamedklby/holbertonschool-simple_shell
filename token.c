#include "shell.h"

/*
 * token_input - Divise (tokenize) l'entrée en tokens
 * @input: L'entrée de l'utilisateur (stdin)
 *
 * Retour: Pas de retour, fonction void
 */
void token_input(char *input)
{
	/* Déclare un pointeur pour stocker chaque token après la division */
	char *split = NULL;

	/* Tableau pour stocker les tokens séparés */
	char *tokens[1024] = {NULL};

	/* Indice pour parcourir le tableau de tokens */
	int index = 0;

	/* Divise la chaîne d'entrée en tokens en utilisant l'espace comme délimiteur */
	split = strtok(input, " ");

	while (split)
	{
		/* Vérifie si le token n'est pas une chaîne vide */
		if (strlen(split) > 0)
		{
			/* Stocke le token dans le tableau des tokens */
			tokens[index] = split;
			index += 1;
		}

		/* Obtient le token suivant */
		split = strtok(NULL, " ");
	}

	/* Si le premier token est NULL (aucune commande entrée), retourne sans rien faire */
	if (tokens[0] == NULL)
	{
		return;
	}

	/* Vérifie les commandes intégrées */
	if (strcmp(tokens[0], "env") == 0)
	{
		/* Si la commande est 'env', appelle la fonction printPrompt */
		printPrompt();   
		return;
	}

	/* Si la commande est 'exit' et n'a pas d'arguments supplémentaires, quitter */
	if (strcmp(tokens[0], "exit") == 0 && tokens[1] == NULL)
	{
		/* Si la commande est 'exit' sans arguments, libère la mémoire et quitte le programme */
		free(tokens[0]);
		exit(0);
	}

	/* Duplique le premier token avant de le modifier */
	split = strdup(tokens[0]);

	/* Récupère le chemin complet pour la commande */
	tokens[0] = _getpath(tokens[0]);

	/* Si un chemin valide est trouvé, libère la mémoire et exécute la commande */
	if (tokens[0] != NULL)
	{
		/* Libère la mémoire allouée pour la duplication du token */
		free(split);               
		/* Exécute la commande avec les tokens obtenus */
		executable(tokens, input); 
		/* Libère la mémoire allouée pour le chemin de la commande */
		free(tokens[0]);           
		return;
	}

	/* Si la commande n'est pas trouvée, affiche une erreur et quitte avec le statut 127 */
	fprintf(stderr, "./hsh: 1: %s: not found\n", split);
	/* Libère la mémoire allouée pour le token dupliqué */
	free(split);                
	/* Quitte le programme avec le statut 127, indiquant une erreur */
	exit(127);                   
}

