/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nokosse <nokosse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:33:42 by kvisouth          #+#    #+#             */
/*   Updated: 2023/06/22 17:00:10 by nokosse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Fonction qui sera executee si il y a 1 ou plusieurs pipes dans la commande.
// ls -l | wc -l
// la sortie de "ls -l" n'est pas affichee dans le terminal mais est envoyee a l'entree de "wc -l".
// "wc -l" s'execute avec le path avec comme entree : la sortie de "ls -l".
void	exec_pipe(t_cmd *cmd, char **envp)
{
	printf("DEBUT fonction exec_pipe\n");
	int i = 0;
	t_cmd *tmp = cmd;
	while (tmp)
	{
		printf ("Command %d : %s / ", i, tmp->tokens[0]);
		printf ("Parameter is : %s\n", tmp->tokens[1]);
		i++;
		tmp = tmp->next;
	}
	printf("FIN fonction exec_pipe\n");
	(void)	envp;
}