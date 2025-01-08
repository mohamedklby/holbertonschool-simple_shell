#include "main.h"  /* Inclut le fichier principal contenant des fonctions et des déclarations nécessaires */

/**
 * main - Point d'entrée du programme
 *
 * Return: 0 si tout s'est bien passé
 */
int main(void)
{
    char *input = NULL;  /* Déclare un pointeur pour stocker l'entrée de l'utilisateur */
    size_t len_input = 0;  /* Variable pour définir la taille du buffer de l'entrée */
    ssize_t read = 0;  /* Variable pour stocker le nombre de caractères lus */

    /* Boucle infinie pour continuer à recevoir des entrées */
    while (1)
    {
        /* Vérifie si le programme est exécuté dans un terminal */
        if (isatty(STDIN_FILENO))  /* Si l'entrée vient d'un terminal, on affiche un prompt */
        {
            printf("$ ");  /* Affiche un prompt "$ " à l'utilisateur */
            fflush(stdout);  /* S'assure que le prompt est affiché immédiatement */
        }

        /* Lit l'entrée de l'utilisateur */
        read = getline(&input, &len_input, stdin);  /* Lit une ligne de texte depuis l'entrée standard */
        if (read == EOF)  /* Si l'utilisateur appuie sur "Ctrl+D" ou si la fin du fichier est atteinte */
        {
            free(input);  /* Libère la mémoire allouée pour l'entrée */
            exit(0);  /* Quitte le programme proprement avec un code 0 (succès) */
        }
        /* Si l'entrée se termine par un saut de ligne, on le remplace par un caractère nul pour supprimer le saut de ligne */
        if (read > 0 && input[read - 1] == '\n')  /* Si la dernière lettre est un saut de ligne */
        {
            input[read - 1] = '\0';  /* Remplace le saut de ligne par un caractère nul */
        }

        /* Traite l'entrée de l'utilisateur */
        token_input(input);  /* Cette fonction est utilisée pour analyser ou traiter l'entrée */
    }
    free(input);  /* Libère la mémoire allouée pour l'entrée avant de quitter */
    return (0);  /* Retourne 0 pour indiquer que tout s'est bien passé */
}
