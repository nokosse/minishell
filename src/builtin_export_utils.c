/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:57:13 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/26 13:25:33 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Count the number of arrays in cmd
*/
int	exp_count_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

/*
Count the number of arrays in env
*/
int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/*
This function will return 1 if 'var' already exist in the env.
Else, it will return 0.
*/
int	var_already_exist(char *var, t_mini *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], var, ft_strlen(var)))
			return (1);
		i++;
	}
	return (0);
}

/*
What is a valid argument for export ?
For variable name :
- First char must be alphabetical or underscore.
- The rest can be alphanumeric or underscore.
*/
int	exp_check_args(char **cmd)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		k = 0;
		if (cmd[i][0] == '=')
			return (ft_putstr_fd("export: invalid variable\n", 2), 0);
		while (cmd[i][j] != '=' && cmd[i][j] != '\0')
			j++;
		while (k < j)
		{
			if (k == 0 && (!ft_isalpha(cmd[i][k]) && cmd[i][k] != '_'))
				return (ft_putstr_fd("export: invalid variable\n", 2), 0);
			if (k > 0 && (!ft_isalnum(cmd[i][k]) && cmd[i][k] != '_'))
				return (ft_putstr_fd("export: invalid content\n", 2), 0);
			k++;
		}
		i++;
	}
	return (1);
}
