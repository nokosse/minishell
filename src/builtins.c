/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:26:17 by kvisouth          #+#    #+#             */
/*   Updated: 2023/06/05 12:10:31 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// This function will return 1 if cmd is :
// echo (with or without -n)
// cd
// export
// unset
// env
// exit

// TODO : trim cmd before strncmp
int check_builtins(char *cmd)
{
	// printf("cmd = %s\n", cmd);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0) // command not found in check_path
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0) // command not found in check_path
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0) // command not found in check_path
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

void	exec_builtins(char **cmd, char **envp)
{
	// printf("executing builtins\n");
	// printf("cmd[0] = %s\n", cmd[0]);
	cmd[0] = ft_strrchr(cmd[0], '/') + 1;
	(void) envp;
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		builtin_echo(cmd);
	// if (ft_strcmp(cmd[0], "cd") == 0)
	// 	builtin_cd(cmd, envp);
	// if (ft_strcmp(cmd[0], "export") == 0)
	// 	builtin_export(cmd, envp);
	// if (ft_strcmp(cmd[0], "unset") == 0)
	// 	builtin_unset(cmd, envp);
	// if (ft_strcmp(cmd[0], "env") == 0)
	// 	builtin_env(cmd, envp);
	// if (ft_strcmp(cmd[0], "exit") == 0)
	// 	builtin_exit(cmd, envp);
}