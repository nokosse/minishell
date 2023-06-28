/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nokosse <nokosse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:33:42 by kvisouth          #+#    #+#             */
/*   Updated: 2023/06/22 18:39:02 by nokosse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Fonction qui sera executee si il y a 1 ou plusieurs pipes dans la commande.
// ls -l | wc -l
// la sortie de "ls -l" n'est pas affichee dans le terminal mais est envoyee a l'entree de "wc -l".
// "wc -l" s'execute avec le path avec comme entree : la sortie de "ls -l".
void exec_pipe(t_cmd *cmd, char **env)
{
    int num_cmds = 0;
    t_cmd *tmp = cmd;

    while (tmp)
    {
        num_cmds++;
        tmp = tmp->next;
    }
    int (*pipes)[2] = malloc((num_cmds - 1) * sizeof(int[2])); // Tableau de tubes

    // Création des tubes
    int i = 0;
    while (i < num_cmds - 1) {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
        i++;
    }

    i = 0;
    tmp = cmd;
    int status;
    pid_t pid;

    while (tmp)
    {
        pid = fork();
        if (pid == -1) 
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            // Processus enfant

            // Redirection des descripteurs de fichiers d'entrée/sortie si nécessaire
            if (i != 0)
            {
                if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(1);
                }
            }
            if (i != num_cmds - 1)
            {
                if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(1);
                }
            }

            // Fermeture des descripteurs de fichiers inutilisés
            int j = 0;
            while (j < num_cmds - 1)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
            }

            // Exécution de la commande
            exec_cmd(tmp, &env);
            exit(1);
        }
        else
        {
            // Processus parent

            // Fermeture des descripteurs de fichiers inutilisés
            if (i != 0) {
                close(pipes[i - 1][0]);
            }
            if (i != num_cmds - 1) {
                close(pipes[i][1]);
            }

            i++;
            tmp = tmp->next;
        }
    }

    // Fermeture des descripteurs de fichiers restants dans le processus parent
    i = 0;
    while (i < num_cmds - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }

    // Attente de la terminaison de tous les processus fils
    while (wait(&status) > 0);

    free(pipes);
    (void)env;			//attention, risque de supprimer environnement lors de pipes
}
