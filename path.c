#include "main.h"  /* Inclut le fichier principal contenant des fonctions et des déclarations nécessaires */

/**
 * _getpath - Fonction qui trouve le chemin pour exécuter une commande
 *
 * @command: La commande entrée par l'utilisateur
 *
 * Return: Le chemin de la commande si trouvé, ou NULL si aucun chemin n'est trouvé
 */
char *_getpath(char *command)
{
    int i = 0;  /* Déclare une variable pour parcourir les éléments de l'environnement */
    char *token = NULL;  /* Déclare un pointeur pour stocker les différentes parties de l'environnement */
    char *cache;  /* Pointeur pour stocker une copie de chaque variable d'environnement */
    char *result = NULL;  /* Pointeur pour stocker le chemin final de la commande */

    /* Si la commande contient déjà un '/', il s'agit d'un chemin absolu, donc retourne la commande telle quelle */
    if (strchr(command, '/') != NULL)
        return (strdup(command));  /* Retourne une copie de la commande si un chemin est fourni */

    /* Parcours chaque variable d'environnement */
    while (environ[i])  /* Tant qu'il y a des éléments dans l'environnement */
    {
        cache = strdup(environ[i]);  /* Crée une copie de la variable d'environnement actuelle */
        token = strtok(cache, "=");  /* Sépare la variable d'environnement au signe égal pour obtenir "PATH" */
        
        /* Si la variable d'environnement est "PATH", on la traite pour trouver le chemin */
        if (strcmp(token, "PATH") == 0)
        {
            token = strtok(NULL, "=");  /* Obtient la valeur de la variable PATH après le signe égal */
            token = strtok(token, ":");  /* Sépare les différentes parties du chemin (les répertoires séparés par ':') */
            
            /* Parcours chaque répertoire dans le PATH */
            while (token)
            {
                /* Alloue de la mémoire pour le chemin complet (répertoire + commande) */
                result = malloc(strlen(token) + strlen(command) + 2);  /* +2 pour le '/' et le caractère nul à la fin */
                if (result == NULL)  /* Si l'allocation échoue */
                {
                    perror("Malloc is NULL");  /* Affiche un message d'erreur */
                    return (NULL);  /* Retourne NULL si l'allocation échoue */
                }

                /* Concatène le répertoire et la commande pour créer un chemin complet */
                sprintf(result, "%s/%s", token, command);

                /* Vérifie si le fichier existe et est exécutable */
                if (access(result, X_OK) == 0)
                {
                    free(cache);  /* Libère la mémoire allouée pour la variable d'environnement */
                    return (result);  /* Retourne le chemin trouvé si le fichier est exécutable */
                }
                free(result);  /* Libère la mémoire allouée pour le chemin si le fichier n'est pas exécutable */
                token = strtok(NULL, ":");  /* Passe au répertoire suivant dans le PATH */
            }
        }
        free(cache);  /* Libère la mémoire allouée pour la variable d'environnement */
        i++;  /* Passe à la variable d'environnement suivante */
    }
    free(command);  /* Libère la mémoire allouée pour la commande entrée par l'utilisateur */
    return (NULL);  /* Retourne NULL si aucun chemin n'a été trouvé pour la commande */
}
