/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:35:52 by operez            #+#    #+#             */
/*   Updated: 2023/06/02 14:53:35 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			// ft_printf("command valid\n");
			return (1);
		}
		i++;
	}
	// ft_printf("Command not found\n");
	return (0);
}

void	executor(char **tokens, char **envp)
{
	pid_t	pid;
	int	status;

	if (check_path(tokens, envp))
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
		{
			// check for builtins command priority
			printf("check_builtins returned %d\n", check_builtins(tokens[0]));
			printf("tokens[0] = %s\n", tokens[0]);
			if (check_builtins(tokens[0]))
			{
				printf("Its a built in\n");
				exec_builtins(tokens, envp);
			}
			else
				if (execve(tokens[0], tokens, NULL) == -1)
					perror("error");
		}
	}
}
