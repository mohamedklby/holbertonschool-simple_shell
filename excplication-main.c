#include "main.h"

void executable(char *argv[], char *input)
{
    int status;  // **Variable pour stocker le statut du processus enfant après sa terminaison**
    int status_exit;  // **Variable pour contenir le code de sortie du processus enfant**
    pid_t child;  // **Variable pour stocker l'ID du processus enfant**

    /* Vérification des permissions d'exécution */
    // **Cette section vérifie si le fichier passé en argument est exécutable à l'aide de la fonction access().**
    // **Si ce n'est pas le cas, un message d'erreur est affiché et le programme se termine avec un code d'erreur 127.**
    if (access(argv[0], X_OK) != 0)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
        free(argv[0]);
        exit(127);
    }

    /* Création du processus enfant */
    // **Ici, on crée un processus enfant avec la fonction fork().**
    // **Le processus enfant et le parent suivent un chemin différent :**
    // **Le parent attend que l'enfant termine, et l'enfant exécute le fichier.**
    child = fork();

    /* Gestion des erreurs lors de la création du processus */
    // **Si le fork() échoue, un message d'erreur est affiché et le programme se termine.**
    if (child == -1)
    {
        perror("Fail Fork\n");
        exit(0);
    }
    /* Exécution du fichier dans le processus enfant */
    // **Dans le processus enfant (lorsque child == 0), on remplace le processus actuel**
    // **par le fichier à exécuter avec execve(). Si execve() échoue, un message d'erreur**
    // **est affiché et le processus enfant termine son exécution.**
    else if (child == 0)
    {
        execve(argv[0], argv, environ);
        perror("Execve Failed");
        free(argv[0]);
        exit(0);
    }
    
    /* Attente de la fin du processus enfant dans le parent */
    // **Le processus parent attend la fin de l'exécution du processus enfant avec wait().**
    // **Une fois que l'enfant est terminé, le code de sortie du processus enfant est récupéré.**
    // **Si le processus enfant a échoué (code de sortie non nul), le parent libère la mémoire et termine.**
    else
    {
        wait(&status);

        if (WIFEXITED(status))
        {
            status_exit = WEXITSTATUS(status);

            if (status_exit != 0)
            {
                free(argv[0]);
                free(input);
                exit(2);
            }
        }
    }
}
