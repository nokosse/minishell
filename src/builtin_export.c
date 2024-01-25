/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:48:23 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/25 15:26:32 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function will update the value (everything after '=' in env)
of the variable 'var'.
*/
int	update_var(char *var, char *value, t_mini *shell)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], var, ft_strlen(var)))
		{
			str = ft_strjoin(var, value);
			if (!str)
				return (0);
			free(shell->env[i]);
			shell->env[i] = str;
			return (1);
		}
		i++;
	}
	return (0);
}

/*
This function will just add an array to env.
That array will just be var + value.

But the tricky part is that we need to env to have more space to fit the new
array. (an additional sizeof(char *)).
It will first malloc a new_env with the actual size of env + 2
1 for the new array to add, and 1 for NULL.
Then, we will COPY the env to new_env.
Then, we will ADD the new array to new_env.
Finally, replace env with new_env and free env.
*/
int	create_var(char *var, char *value, t_mini *shell)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = NULL;
	new_env = malloc(sizeof(char *) * (env_count(shell->env) + 2));
	if (!new_env)
		return (0);
	while (shell->env[i])
	{
		new_env[i] = ft_strdup(shell->env[i]);
		if (!new_env[i])
			return (0);
		i++;
	}
	new_env[i] = ft_strjoin(var, value);
	if (!new_env[i])
		return (0);
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (1);
}

/*
This function will store in var the variable name, and in value the value.
Then it will check if the variable already exist.
If it does, it will update the value.
Else, it will create a new variable and assign the value.
*/
int	exp_handle_var(char *cmd, t_mini *shell)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	while (cmd[i] != '=')
		i++;
	var = ft_substr(cmd, 0, i);
	value = ft_substr(cmd, i, ft_strlen(cmd));
	if (!var || !value)
		return (0);
	if (var_already_exist(var, shell))
	{
		if (!update_var(var, value, shell))
			return (0);
	}
	else
	{
		if (!create_var(var, value, shell))
			return (0);
	}
	return (1);
}

/*
This function will be the core of the export command.
All the arguments are valid, now it will handle them.
*/
int	exp_handle_args(char **cmd, t_mini *shell)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j] != '\0' && cmd[i][j] != '=')
			j++;
		if (cmd[i][j] == '=')
		{
			if (!exp_handle_var(cmd[i], shell))
				return (0);
		}
		i++;
	}
	return (1);
}

/*
Export will take at least 1 argument.
If not, does nothing.
Only if all the arguments are valid, the command will be executed.
*/
int	builtin_export(char **cmd, t_mini *shell)
{
	if (exp_count_args(cmd) <= 1)
		return (1);
	if (!exp_check_args(cmd))
		return (0);
	if (!exp_handle_args(cmd, shell))
		return (0);
	return (1);
}
