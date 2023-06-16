/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:35:52 by operez            #+#    #+#             */
/*   Updated: 2023/06/16 18:16:52 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_path(char **tokens, char **envp)
{
	int		i;
	char	*path;
	char	**split;
	char	*command;

	i = 0;
		path = ft_strdup(getenv("PATH"));
	(void) envp;
	split = ft_split(path, ':');
	while (split[i])
	{
		split[i] = ft_strjoin(split[i], "/");
		command = ft_strjoin(split[i], tokens[0]);			//gere que la premiere commande pour l instant
		command = ft_strtrim(command, " ");
		// ft_printf("command = %s\n", command);
		if (access(command, X_OK) == 0)
		{
			tokens[0] = command;
			// ft_printf("command valid\n");
			return (1);
		}
		i++;
	}
	ft_printf("Command not found\n");
	return (0);
}

// free tmp plus tard
// Retourne le nombre de commandes.
// faire i-1 pour le nombre de pipes.
int	count_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

// TODO : implementer clear (variable d'env TERM)
// TODO : executer toute les commandes entre pipes
// TODO : gerer les redirections < > << >>
// TODO : gerer les variables d'environnement (un $ suivi d'un mot)
// TODO : gerer $? ? qui doit être substitué par le statut de sortie
//		de la dernière pipeline exécutée au premier plan

// 1. check si il y a des pipe.
// 2. check si il y a des redirections.

void	executor(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	// si count_cmd > 1 : il y a au moins 1 pipe.
	// donc on execute la fonction pour executer les commandes avec pipes.
	if (count_cmd(cmd) > 1)
		printf("NBR OF PIPEs : %d\n", count_cmd(cmd) - 1);
 
	// Il check d'abord si la commande est un commande built-in
	if (check_builtins(cmd->tokens[0]))
		exec_builtins(cmd->tokens, envp); 

	// Si c'est pas une commande built-in (echo, cd, export etc..)
	// On va check pour executer la commande avec PATH (ls, cat etc..)
	else
	{
		if	(check_path(cmd->tokens, envp))
		{
			pid = 0;
			status = 0;
			pid = fork();
			if (pid > 0)
			{
				waitpid(pid, &status, 0);
				kill(pid, SIGTERM);
			}
			else
				if (execve(cmd->tokens[0], cmd->tokens, NULL) == -1)
					perror("error");
		}
	}
}
