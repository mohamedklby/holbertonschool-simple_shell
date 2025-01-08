#include "main.h"  /* Inclut le fichier d'en-tête principal, qui contient probablement des déclarations et des inclusions nécessaires */

/**
 * executable - Exécute un fichier si celui-ci a les permissions d'exécution
 * @argv: Chemin du fichier exécutable (tableau de chaînes, avec argv[0] étant l'exécutable)
 * @input: Entrée donnée par l'utilisateur dans le shell
 * Return: aucune valeur retournée, fonction void
 */
void executable(char *argv[], char *input)
{
    int status;  /* Déclare une variable pour stocker le statut du processus enfant après sa terminaison */
    int status_exit;  /* Variable pour contenir le statut de sortie du processus enfant */
    pid_t child;  /* Déclare une variable pour stocker l'ID du processus du processus enfant */

    /* Vérifie si le fichier pointé par argv[0] est exécutable */
    if (access(argv[0], X_OK) != 0)  /* La fonction access vérifie les permissions du fichier */
    {
        /* Si le fichier n'est pas exécutable, affiche un message d'erreur sur stderr */
        fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
        free(argv[0]);  /* Libère la mémoire allouée pour le chemin du fichier (argv[0]) */
        exit(127);  /* Quitte avec le code de statut 127 (commande non trouvée) */
    }

    /* Crée un nouveau processus avec fork() */
    child = fork();  /* fork() crée un nouveau processus : l'enfant reçoit le PID 0, le parent reçoit le PID de l'enfant */

    /* Si fork() échoue, affiche une erreur et quitte */
    if (child == -1)  /* Erreur lors du fork */
    {
        perror("Fail Fork\n");  /* Affiche un message d'erreur indiquant l'échec du fork() */
        exit(0);  /* Quitte avec le code de statut 0 (échec mais sortie normale) */
    }
    /* Si nous sommes dans le processus enfant (child == 0) */
    else if (child == 0)  
    {
        /* Exécute la commande dans le processus enfant avec execve() */
        execve(argv[0], argv, environ);  /* execve remplace le processus actuel par le fichier à exécuter */
        perror("Execve Failed");  /* Si execve échoue, affiche un message d'erreur */
        free(argv[0]);  /* Libère la mémoire allouée pour argv[0] avant de quitter */
        exit(0);  /* Quitte le processus enfant */
    }
    else  /* Si nous sommes dans le processus parent (child != 0) */
    {
        /* Attend la fin du processus enfant */
        wait(&status);  /* wait() attend que le processus enfant se termine et stocke son statut de sortie dans 'status' */

        /* Si le processus enfant s'est terminé normalement (WIFEXITED vérifie si l'enfant s'est terminé correctement) */
        if (WIFEXITED(status))
        {
            /* Récupère le code de sortie du processus enfant (status_exit contient le code de sortie) */
            status_exit = WEXITSTATUS(status);

            /* Si le processus enfant a quitté avec un statut non nul (indiquant une erreur), libère la mémoire et quitte */
            if (status_exit != 0)  /* Vérifie si le code de sortie de l'enfant n'est pas zéro (indiquant une erreur) */
            {
                free(argv[0]);  /* Libère la mémoire allouée pour argv[0] */
                free(input);  /* Libère la mémoire allouée pour la chaîne d'entrée */
                exit(2);  /* Quitte le processus parent avec le code de statut 2 (échec de la commande) */
            }
        }
    }
}
