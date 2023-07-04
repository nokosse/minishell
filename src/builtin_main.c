/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:26:17 by kvisouth          #+#    #+#             */
/*   Updated: 2023/06/13 11:01:55 by kvisouth         ###   ########.fr       */
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
int check_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	return (0);
}

// This function will execute the right builtin function depending on the cmd
void	exec_builtins(t_cmd **cmd, char **tokens, char ***env)
{
	if (ft_strcmp(tokens[0], "echo") == 0)
		builtin_echo(tokens);
	if (ft_strcmp(tokens[0], "cd") == 0)
	 	builtin_cd(tokens);
	if (ft_strcmp(tokens[0], "pwd") == 0)
	 	builtin_pwd();
	if (ft_strcmp(tokens[0], "export") == 0)
	 	*env = builtin_export(tokens, *env);
	if (ft_strcmp(tokens[0], "unset") == 0)
	 	*env = builtin_unset(tokens, *env);
	if (ft_strcmp(tokens[0], "env") == 0)
	 	builtin_env(*env);
	if (ft_strcmp(tokens[0], "exit") == 0)
	 	builtin_exit(cmd, env);
}
