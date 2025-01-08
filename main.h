#ifndef MAIN_H  /* Vérifie si MAIN_H n'est pas déjà défini */
#define MAIN_H  /* Définit MAIN_H pour éviter les inclusions multiples de ce fichier */

#include <stdio.h>  /* Inclut la bibliothèque standard pour les entrées/sorties (printf, scanf, etc.) */
#include <stdlib.h>  /* Inclut la bibliothèque standard pour les fonctions de gestion de la mémoire (malloc, free, exit, etc.) */
#include <string.h>  /* Inclut la bibliothèque standard pour les fonctions de manipulation de chaînes (strlen, strcpy, etc.) */
#include <unistd.h>  /* Inclut la bibliothèque pour les fonctions liées aux processus et à l'exécution (fork, exec, etc.) */
#include <sys/wait.h>  /* Inclut la bibliothèque pour gérer l'attente des processus enfants (wait, waitpid) */
#include <sys/types.h>  /* Inclut la bibliothèque pour les définitions de types utilisés dans les systèmes Unix (pid_t, etc.) */

extern char **environ;  /* Déclare la variable d'environnement (tableau de chaînes de caractères) */

void token_input(char *input);  /* Déclare la fonction qui traitera l'entrée de l'utilisateur en la divisant en tokens */
void executable(char **argv, char *input);  /* Déclare la fonction pour exécuter un fichier, si les permissions sont correctes */
char *_getpath(char *cmd);  /* Déclare la fonction qui cherche le chemin d'un fichier exécutable à partir de la commande */
void print_env(void);  /* Déclare la fonction pour afficher les variables d'environnement */

#endif  /* Fin de la vérification de l'inclusion multiple */
