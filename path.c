#include "main.h"  /* **Inclut le fichier principal contenant des fonctions et des déclarations nécessaires** */

/**
 * _getpath - Fonction qui trouve le chemin pour exécuter une commande
 *
 * @command: La commande entrée par l'utilisateur
 *
 * Return: Le chemin de la commande si trouvé, ou NULL si aucun chemin n'est trouvé
 */
char *_getpath(char *command)
{
    int i = 0;  /* **Initialisation d'une variable pour parcourir l'environnement** */
    char *token = NULL;  /* **Pointeur pour traiter chaque partie de la variable d'environnement** */
    char *cache;  /* **Pointeur temporaire pour stocker une copie de chaque variable d'environnement** */
    char *result = NULL;  /* **Pointeur pour stocker le chemin final de la commande** */

    /* Vérification si la commande contient un chemin absolu */
    // **Si la commande contient déjà un '/', cela signifie qu'un chemin absolu est fourni, donc on retourne directement la commande telle quelle.**
    if (strchr(command, '/') != NULL)
        return (strdup(command));  /* **Retourne une copie de la commande si un chemin est fourni** */

    /* Parcours chaque variable d'environnement */
    // **Si la commande ne contient pas de chemin, on commence à chercher dans les variables d'environnement (spécifiquement PATH).**
    while (environ[i])  /* **On parcourt chaque variable d'environnement** */
    {
        cache = strdup(environ[i]);  /* **Création d'une copie de la variable d'environnement actuelle pour éviter de la modifier directement.** */
        token = strtok(cache, "=");  /* **On découpe la variable d'environnement à partir du signe '=' pour obtenir le nom de la variable (par exemple, "PATH").** */
        
        /* Vérification si la variable d'environnement est "PATH" */
        if (strcmp(token, "PATH") == 0)
        {
            token = strtok(NULL, "=");  /* **On obtient la valeur associée à "PATH", c'est-à-dire la liste des répertoires séparés par des ":"** */
            token = strtok(token, ":");  /* **On sépare les répertoires dans le PATH (chaque répertoire est séparé par ':').** */
            
            /* Recherche dans chaque répertoire du PATH */
            // **On commence à parcourir chaque répertoire du PATH pour vérifier si la commande existe dans l'un de ces répertoires.**
            while (token)
            {
                /* Construction du chemin complet pour la commande */
                result = malloc(strlen(token) + strlen(command) + 2);  /* **On alloue de la mémoire pour le chemin complet (répertoire + commande).** */
                if (result == NULL)  /* **Si l'allocation échoue, on retourne NULL.** */
                {
                    perror("Malloc is NULL");  /* **Affiche un message d'erreur si l'allocation échoue.** */
                    return (NULL);  /* **Retourne NULL si l'allocation échoue.** */
                }

                /* Concaténation du répertoire et de la commande pour créer le chemin complet */
                sprintf(result, "%s/%s", token, command);  /* **On crée le chemin complet (répertoire + commande).** */

                /* Vérification de l'existence et de l'exécutabilité du fichier */
                // **On vérifie si un fichier exécutable existe à ce chemin.**
                if (access(result, X_OK) == 0)
                {
                    free(cache);  /* **Libère la mémoire allouée pour la variable d'environnement après utilisation.** */
                    return (result);  /* **Retourne le chemin complet si le fichier est exécutable.** */
                }
                free(result);  /* **Libère la mémoire allouée pour le chemin si le fichier n'est pas exécutable.** */
                token = strtok(NULL, ":");  /* **Passe au répertoire suivant dans le PATH.** */
            }
        }
        free(cache);  /* **Libère la mémoire allouée pour la variable d'environnement après traitement.** */
        i++;  /* **Passe à la variable d'environnement suivante.** */
    }
    free(command);  /* **Libère la mémoire allouée pour la commande entrée par l'utilisateur.** */
    return (NULL);  /* **Retourne NULL si aucun chemin valide n'a été trouvé.** */
}
