/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:35:52 by operez            #+#    #+#             */
/*   Updated: 2023/06/14 10:24:36 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// This function will duplicate the envp.
// void	dup_env(char **envp)
// {
	
// }

// int	check_path(char **tokens, char **envp)
// {
// 	int		i;
// 	char	*path;
// 	char	**split;
// 	char	*command;

// 	i = 0;
// 		path = ft_strdup(getenv("PATH"));
// 	printf("path = %s\n", path);
// 	(void) envp;
// 	split = ft_split(path, ':');
// 	while (split[i])
// 	{
// 		split[i] = ft_strjoin(split[i], "/");
// 		command = ft_strjoin(split[i], tokens[0]);			//gere que la premiere commande pour l instant
// 		ft_printf("command = %s\n", command);
// 		if (access(command, X_OK) == 0)
// 		{
// 			tokens[0] = command;
// 			ft_printf("command valid\n");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	ft_printf("Command not found\n");
// 	return (0);
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
			ft_printf("command valid\n");
			return (1);
		}
		i++;
	}
	ft_printf("Command not found\n");
	return (0);
}

// Peut etre je dois deplacer check_builtins au dessus du if check_path parceque
// les commandes cd, export et unset retournent 0 dans check_path
// ducoup check_builtins ne sera jamais appele pour ces builtins en question justement

// TODO : implementer clear (variable d'env TERM)
// TODO : executer toute les commandes entre pipes
// TODO : gerer les redirections < > << >>
// TODO : gerer les variables d'environnement (un $ suivi d'un mot)
// TODO : gerer $? ? qui doit être substitué par le statut de sortie
//		de la dernière pipeline exécutée au premier plan

// OLD EXECUTOR WITH CHAR **TOKENS, NEW EXECUTOR WILL TAKE A T_LIST *CMD.

void	executor(char **tokens, char **envp)
{
	pid_t	pid;
	int		status;
	char	*envcpy; //copie de envp
	(void) envcpy;

	// On met une copie de envp (environment) dans envp_copy

	// Il check d'abord si la commande est un commande built-in
	if (check_builtins(tokens[0]))
		exec_builtins(tokens, envp);

	// Si c'est pas une commande built-in (echo, cd, export etc..)
	// On va check pour executer la commande avec PATH (ls, cat etc..)
	else
	{
		if	(check_path(tokens, envp))
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
				if (execve(tokens[0], tokens, NULL) == -1)
					perror("error");
		}
	}
}

// NEW EXECUTOR WITH T_LIST *CMD, OLD EXECUTOR TAKES CHAR **TOKENS

// void	executor(t_cmd cmd, char **envp)
// {
// 	pid_t	pid;
// 	int		status;
	
// 	if (check_builtins(cmd->tokens[0]))
// 	{
// 		printf("executing builtins\n");
// 		exec_builtins(cmd->tokens, envp);
// 	}
// 	else
// 	{
// 		if	(check_path(cmd->tokens, envp))
// 		{
// 			pid = 0;
// 			status = 0;
// 			pid = fork();
// 			if (pid > 0)
// 			{
// 				waitpid(pid, &status, 0);
// 				kill(pid, SIGTERM);
// 			}
// 			else
// 				if (execve(cmd->tokens[0], cmd->tokens, NULL) == -1)
// 					perror("error");
// 		}
// 	}
// }