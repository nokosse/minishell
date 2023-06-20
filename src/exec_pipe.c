/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:33:42 by kvisouth          #+#    #+#             */
/*   Updated: 2023/06/20 16:04:06 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Fonction qui sera executee si il y a 1 ou plusieurs pipes dans la commande.
// ls -l | wc -l
// la sortie de "ls -l" n'est pas affichee dans le terminal mais est envoyee a l'entree de "wc -l".
// "wc -l" s'execute avec le path avec comme entree : la sortie de "ls -l".
void	exec_pipe(t_cmd *cmd, char **envp)
{
	(void)	envp;
	(void)	cmd;
	printf("DEBUT fonction exec_pipe\n");
	int i = 0;
	while (cmd)
	{
		printf ("Command %d : %s / ", i, cmd->tokens[0]);
		printf ("Parameter is : %s\n", cmd->tokens[1]);
		i++;
		cmd = cmd->next;
	}
	printf("FIN fonction exec_pipe\n");
}