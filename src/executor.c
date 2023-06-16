/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:35:52 by operez            #+#    #+#             */
/*   Updated: 2023/06/16 15:30:52 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// This function will duplicate the envp.
// void	dup_env(char **envp)
// {
	
// }

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

// TODO : implementer clear (variable d'env TERM)
// TODO : executer toute les commandes entre pipes
// TODO : gerer les redirections < > << >>
// TODO : gerer les variables d'environnement (un $ suivi d'un mot)
// TODO : gerer $? ? qui doit être substitué par le statut de sortie
//		de la dernière pipeline exécutée au premier plan

void	executor(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	char	*envcpy; //copie de envp
	(void) envcpy;

	// On met une copie de envp (environment) dans envp_copy

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
