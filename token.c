#include "main.h"  /* **Inclut le fichier principal contenant des fonctions et des déclarations nécessaires** */

/**
 * token_input - Divise l'entrée en "tokens" (mots) et traite la commande.
 *
 * @input: L'entrée standard donnée par l'utilisateur (la commande).
 *
 * Return: Pas de valeur retournée, c'est une fonction de type void.
 */
void token_input(char *input)
{
    char *split = NULL;  /* **Déclare un pointeur pour stocker chaque mot extrait de l'entrée** */
    char *tokens[1024] = { NULL };  /* **Déclare un tableau pour stocker les "tokens" (mots) séparés** */
    int index = 0;  /* **Index pour ajouter des tokens dans le tableau tokens** */

    /* Utilisation de strtok pour diviser l'entrée en mots, séparés par des espaces */
    // **On commence par diviser l'entrée en mots, chacun séparé par un espace, à l'aide de la fonction strtok.**
    split = strtok(input, " ");  /* **Sépare la première partie de l'entrée par les espaces** */
    while (split)  /* **Continue tant qu'il y a encore des mots à extraire** */
    {
        /* Si le mot extrait n'est pas vide, l'ajoute dans le tableau des tokens */
        // **Si le mot extrait n'est pas vide, on l'ajoute dans le tableau "tokens" pour le traitement futur.**
        if (strlen(split) > 0)
        {
            tokens[index] = split;  /* **Stocke le token dans le tableau** */
            index += 1;  /* **Passe à l'index suivant du tableau** */
        }
        split = strtok(NULL, " ");  /* **Récupère le token suivant** */
    }

    /* Si aucun token n'a été trouvé, on quitte la fonction */
    // **Si aucun mot n'a été extrait, la fonction termine sans rien faire.**
    if (tokens[0] == NULL)
    {
        return;  /* **Quitte la fonction** */
    }

    /* Si le premier token est "env", on appelle la fonction pour afficher les variables d'environnement */
    // **Si la commande est "env", on affiche les variables d'environnement à l'aide de la fonction print_env.**
    if (strcmp(tokens[0], "env") == 0)
    {
        print_env();  /* **Affiche les variables d'environnement** */
        return;  /* **Quitte la fonction après avoir affiché les variables d'environnement** */
    }

    /* Si le premier token est "exit" et qu'il n'y a pas d'argument supplémentaire, on quitte le programme */
    // **Si la commande est "exit" et qu'il n'y a pas d'argument supplémentaire, le programme quitte.**
    if (strcmp(tokens[0], "exit") == 0 && tokens[1] == NULL)
    {
        free(tokens[0]);  /* **Libère la mémoire allouée pour le token "exit"** */
        exit(0);  /* **Quitte le programme avec un code de statut 0 (succès)** */
    }

    /* Si ce n'est pas une commande spéciale ("env" ou "exit"), on cherche le chemin du fichier exécutable */
    // **Si la commande n'est pas "env" ou "exit", on recherche le chemin du fichier exécutable pour la commande.**
    split = strdup(tokens[0]);  /* **Crée une copie du premier token (le nom de la commande)** */
    tokens[0] = _getpath(tokens[0]);  /* **Cherche le chemin de la commande dans les répertoires du PATH** */
    
    /* Si un chemin valide est trouvé, on exécute la commande */
    // **Si un chemin valide est trouvé pour la commande, on l'exécute.**
    if (tokens[0] != NULL)
    {
        free(split);  /* **Libère la mémoire allouée pour la copie du token** */
        executable(tokens, input);  /* **Exécute la commande avec les arguments** */
        free(tokens[0]);  /* **Libère la mémoire allouée pour le chemin de la commande** */
        return;  /* **Quitte la fonction après l'exécution de la commande** */
    }

    /* Si aucun chemin valide n'a été trouvé pour la commande, affiche une erreur et quitte avec un code 127 */
    // **Si aucun chemin valide n'a été trouvé, affiche un message d'erreur et termine avec un code de statut 
