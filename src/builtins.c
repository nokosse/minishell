/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:48:38 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/23 17:30:26 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function will return 1 if cmd is a builtin command.
such as : echo, pwd, exit, export, unset, cd, env.

'if (cmd)' MAY be useless because the parser return 0 doens't send us
to the executor is cmd is NULL.
But it's an extra security so why not.
*/
int	check_builtins(char *cmd)
{
	if (cmd)
	{
		if (!ft_strcmp(cmd, "echo"))
			return (1);
		else if (!ft_strcmp(cmd, "pwd"))
			return (1);
		else if (!ft_strcmp(cmd, "exit"))
			return (1);
		else if (!ft_strcmp(cmd, "export"))
			return (1);
		else if (!ft_strcmp(cmd, "unset"))
			return (1);
		else if (!ft_strcmp(cmd, "cd"))
			return (1);
		else if (!ft_strcmp(cmd, "env"))
			return (1);
	}
	return (0);
}

int	exec_builtin(char **cmd, t_mini *shell)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (builtin_echo(cmd));
	else if (!ft_strcmp(cmd[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(cmd[0], "exit"))
		builtin_exit(shell, cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		return (builtin_export(cmd, shell));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (builtin_unset(cmd, shell));
	else if (!ft_strcmp(cmd[0], "cd"))
		return (builtin_cd(cmd, shell));
	else if (!ft_strcmp(cmd[0], "env"))
		builtin_env(shell->env);
	return (0);
}
