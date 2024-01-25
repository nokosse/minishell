/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:48:32 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/25 17:07:10 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Count the number of arrays in cmd
*/
int	unset_count_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

/*
A valid argument if unset is a variable name.
A variable name that is valid must start either with a letter, or underscore
And the rest of the name can be either letter, number or underscores.
*/
int	unset_check_args(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (i == 0)
			{
				if (!ft_isalpha(cmd[i][j]) && cmd[i][j] != '_')
					return (0);
			}
			else
			{
				if (!ft_isalnum(cmd[i][j]) && cmd[i][j] != '_')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/*
This function will delete the variable 'var' from env.
It will just litteraly copy the env and erease the variable 'var' from it.
*/
int	delete_var(char *var, t_mini *shell)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = NULL;
	new_env = ft_calloc(env_count(shell->env) + 1, sizeof(char *));
	if (!new_env)
		return (0);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var)))
		{
			new_env[j] = ft_strdup(shell->env[i]);
			if (!new_env[j])
				return (0);
			j++;
		}
		i++;
	}
	free(shell->env);
	shell->env = new_env;
	return (1);
}

/*
This function will go in delet_var() only if the variable exist.
*/
int	unset_handle_args(char **cmd, t_mini *shell)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (var_already_exist(cmd[i], shell))
		{
			if (!delete_var(cmd[i], shell))
				return (0);
		}
		else
			return (1);
		i++;
	}
	return (1);
}

/*
Unset takes 1 or more arguments. It removes the specified variables from 'env'.
For the parsing of the arguments, if the variable name does not exist in 'env',
it does nothing. If there is no argument, it prints an error.
The variable name have to be valid (see unset_check_name()).
*/
int	builtin_unset(char **cmd, t_mini *shell)
{
	if (unset_count_args(cmd) <= 1)
		return(ft_putstr_fd("unset: not enough arguments\n", 2), 1);
	if (!unset_check_args(cmd))
		return (ft_putstr_fd("unset: not a valid identifier\n", 2), 1);
	if (unset_handle_args(cmd, shell))
		return (0);
	return (1);
}