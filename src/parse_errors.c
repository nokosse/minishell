/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:51:12 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/20 15:06:28 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_quote(char *str, char c)
{
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		return (1);
	return (0);
}

int	handle_sq(char *str, int *i, int *sq)
{
	if (str[*i] == '\'')
	{
		if (sq_is_closed(str, *i))
		{
			*sq = 1;
			(*i)++;
			while (str[*i] && str[*i] != '\'')
				(*i)++;
			(*i)++;
		}
		else
			return (0);
	}
	return (1);
}

int	handle_dq(char *str, int *i, int *dq)
{
	if (str[*i] == '\"')
	{
		if (dq_is_closed(str, *i))
		{
			*dq = 1;
			(*i)++;
			while (str[*i] && str[*i] != '\"')
				(*i)++;
			(*i)++;
		}
		else
			return (0);
	}
	return (1);
}

int	quote_error(char *str)
{
	int	i;
	int	dq;
	int	sq;

	i = 0;
	while (str[i])
	{
		dq = 0;
		sq = 0;
		if (!handle_sq(str, &i, &sq))
			return (0);
		if (!handle_dq(str, &i, &dq))
			return (0);
		if (dq == 0 && sq == 0)
			i++;
	}
	return (1);
}

/*
This function will handle the input errors.
*/
int	parse_error(t_mini *shell)
{
	t_cmd	*cmd_t;
	char	*str;
	int		i;

	i = 0;
	cmd_t = shell->cmd;
	while (i < shell->nb_commands)
	{
		str = cmd_t->str;
		if (!quote_error(str))
			return (ft_putstr_fd("minishell: parsing errore\n", 2), 0);
		i++;
		cmd_t = cmd_t->next;
	}
	return (1);
}
