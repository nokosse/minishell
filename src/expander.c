/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:51:28 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/17 09:21:39 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_env(t_mini *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}

/*
This function will just check if there is a $ in the string so we know if we
need to expand it or not.
*/
int	is_to_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

/*
This function will search for the variable str in our environnement table.
*/
int	search_in_env(t_mini *shell, char *str)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (str[0] == '$' && str[1] != '\0')
			str++;
		if (!ft_strncmp(shell->env[i], str, ft_strlen(str)))
			return (1);
		i++;
	}
	return (0);
}

/*
This function will replace str which is a non existing variable, to an empty
string.
*/
int	expand_to_empty(char **str)
{
	*str = ft_strdup("");
	if (!*str)
		return (0);
	return (1);
}

char	*get_var_content(t_mini *shell, char *str)
{
	int		i;
	int		j;
	char	*var_content;

	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (str[0] == '$' && str[1] != '\0')
			str++;
		if (!ft_strncmp(shell->env[i], str, ft_strlen(str)))
		{
			while (shell->env[i][j] != '=')
				j++;
			var_content = ft_strdup(shell->env[i] + j + 1);
			if (!var_content)
				return (NULL);
			return (var_content);
		}
		i++;
	}
	return (NULL);
}

int	expand_to_env(char **str, t_mini *shell)
{
	char	*var_content;

	var_content = get_var_content(shell, *str);
	if (!var_content)
		return (0);
	*str = var_content;
	return (1);	
}

/*
This function is called in the case str is not in quotes, meaning that str
IS starting with a $ and IS just a simple variable.
str WILL look like : $USER, $PATH, $PWD, etc.. so it's easy to handle..?
*/
int	handle_expansion(t_mini *shell, char **str)
{
	printf("%s will be expanded\n", *str);
	if (!search_in_env(shell, *str))
	{
		if (!expand_to_empty(str))
			return (0);
	}
	else
	{
		if (!expand_to_env(str, shell))
			return (0);
	}
	return (1);
}

/*
The expander takes variables, identified by $, and replaces them with their
value from the environment variables. Such that $USER becomes kvisouth
and $? is replaced with the exit code.
Non existing variables are replaced by an empty string. (str[0] = '\0')
*/
int	expander(t_mini *shell)
{
	t_cmd	*cmd_t;
	int		i;
	int		j;

	i = 0;
	cmd_t = shell->cmd;
	while (i < shell->nb_commands)
	{
		j = 0;
		while (cmd_t->cmd[j])
		{
			if (!is_quote(cmd_t->cmd[j], '\'') && !is_quote(cmd_t->cmd[j], '\"')
				&& is_to_expand(cmd_t->cmd[j]))
			{
				if (!handle_expansion(shell, &cmd_t->cmd[j]))
					return (0);
			}
			j++;
		}
		cmd_t = cmd_t->next;
		i++;
	}
	return (1);
}
