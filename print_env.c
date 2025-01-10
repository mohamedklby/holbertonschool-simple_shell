#include "main.h"  /* **Inclut le fichier principal contenant des fonctions et des déclarations nécessaires** */

/**
 * print_env - Affiche les variables d'environnement.
 *
 * Cette fonction imprime les variables d'environnement sur la sortie standard.
 * Chaque variable d'environnement est affichée sur une nouvelle ligne.
 *
 * Return: Pas de valeur retournée, c'est une fonction de type void.
 */
void print_env(void)
{
    char **env;  /* **Déclare un pointeur de type tableau de chaînes de caractères pour parcourir les variables d'environnement** */

    /* Parcourt toutes les variables d'environnement jusqu'à ce que le pointeur arrive à NULL */
    // **Ici, on commence à parcourir le tableau environ qui contient les variables d'environnement jusqu'à atteindre un pointeur NULL, indiquant la fin du tableau.**
    for (env = environ; *env != NULL; env++)  /* **'environ' est un tableau contenant les variables d'environnement.** */
    {
        printf("%s\n", *env);  /* **Affiche chaque variable d'environnement suivie d'un saut de ligne.** */
    }
}
