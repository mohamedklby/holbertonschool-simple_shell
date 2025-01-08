#include "shell.h"

/*
 * _getpath - Fonction qui trouve le chemin pour exécuter une commande.
 *
 * @command: Commande saisie par l'utilisateur en entrée.
 * Return: La commande si elle contient '/'
 * avec PATH ou NULL si rien n'est trouvé.
 */
char *_getpath(char *command)
{
	int i = 0;
	char *token = NULL;
	char *cache;
	char *result = NULL;

	/* Si la commande contient '/', renvoyer une copie de la command */
	if (strchr(command, '/') != NULL)
		return (strdup(command));

	/* Parcourir les variables d'environnement */
	while (environ[i])
	{
		/* Dupliquer la variable d'environnement pour éviter la modification */
		cache = strdup(environ[i]);
		/*Extraire le premier token jusqu au '=' */
		token = strtok(cache, "=");
		/*Si le token correspond à "PATH" */
		if (strcmp(token, "PATH") == 0)
		{
			/* Extraire la partie après le '=' */
			token = strtok(NULL, "=");
			/*Diviser le chemin en morceaux en utilisant ':' comme délimiteur */
			token = strtok(token, ":");
			while (token)
			{
				/* Allouer de la mémoire pour stocker le résultat */
				result = malloc(strlen(token) + strlen(command) + 2);

				/* Gérer l'échec de l'allocation mémoire */
				if (result == NULL)
				{
					perror("Malloc is NULL");
					return (NULL);
				}
				/* Concaténer le chemin et la commande */
				sprintf(result, "%s/%s", token, command);

				/* Vérifier si le fichier est exécutable */
				if (access(result, X_OK) == 0)
				{
					free(cache);
					return (result);
				}

				/* Libérer la mémoire allouée pour le résultat */
				free(result);

				/* Passer au prochain morceau du chemin */
				token = strtok(NULL, ":");
			}
		}

		/* Libérer la mémoire allouée pour la variable d'environnement dupliquée */
		free(cache);

		/* Passer à la variable d'environnement suivante */
		i++;
	}

	/* Libérer la mémoire allouée pour la commande */
	free(command);

	/* Aucun chemin trouvé, renvoyer NULL */
	return (NULL);
}
