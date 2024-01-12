/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:51:28 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/12 19:24:41 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Returns 1 if str is between single quotes, 0 otherwise.
*/
int	is_single_quote(char *str)
{
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (1);
	return (0);
}

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

int	handle_expansion(t_mini *shel	l, char *str)
{
	(void)shell;
	printf("str = %s\n", str);
	return (1);
}

int	find_env_var(t_mini *shell)
{
	t_cmd	*cmd_t;
	int		i;
	int		j;

	i = 0;
	cmd_t = shell->cmd;
	while (i < shell->nb_commands) // iterate over commands
	{
		j = 0;
		while (cmd_t->cmd[j]) // iterate over arguments
		{
			if (!is_single_quote(cmd_t->cmd[j]) && is_to_expand(cmd_t->cmd[j]))
			{
				if (!handle_expansion(shell, cmd_t->cmd[j]))
					return (0);
			}
			j++;
		}
		cmd_t = cmd_t->next;
		i++;
	}
	return (1);
}

/*
The expander takes variables, identified by $, and replaces them with their
value from the environment variables. Such that $USER becomes kvisouth
and $? is replaced with the exit code.
*/
int	expander(t_mini *shell)
{
	if (!find_env_var(shell))
		return (0);
	return (1);
}
