/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:51:12 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/19 18:11:20 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_quote(char *str, char c)
{
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		return (1);
	return (0);
}

int	is_insique_any_quote(char *str, int i)
{
	int	right_quote;
	int	left_quote;

	right_quote = 0;
	left_quote = 0;
	while (i > 0)
	{
		if (str[i] == '\"' || str[i] == '\'')
			left_quote = 1;
		i--;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			right_quote = 1;
		i++;
	}
	if (!right_quote || !left_quote)
		return (0);
	return (1);
}

/*
This function MAY be useless since handle_pipe_err1 in lexer_errors.c
may handle most/all of the pipe errors.
*/
int	pipe_error(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|' && !is_insique_any_quote(cmd, i))
		{
			if (cmd[i + 1] == '|')
				return (0);
			if (cmd[i - 1] == '|')
				return (0);	
		}
		i++;
	}
	return (1);
}

/*
This function  will check if there is an odd number of double quotes.
Returns 0 if there is an odd number of double quotes.
ofc, ignore the double quotes inside single quotes.
*/
int	dquote_error(char *str)
{
	int			i;
	static int	nb_dq;

	i = 0;
	nb_dq = 0;
	while (str[i])
	{
		if (!is_inside_sq(i, str))
		{
			if (str[i] == '\"')
			{
				nb_dq++;	
			}
		}
		i++;
	}
	printf("nb_dq = %d\n", nb_dq);
	if (nb_dq % 2 != 0)
		return (0);
	return (1);
}

int	squote_error(char *str)
{
	int			i;
	static int	nb_sq;

	i = 0;
	nb_sq = 0;
	while (str[i])
	{
		if (!is_inside_dq(i, str))
		{
			if (str[i] == '\'')
			{
				nb_sq++;	
			}
		}
		i++;
	}
	printf("nb_sq = %d\n", nb_sq);	
	if (nb_sq % 2 != 0)
		return (0);
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
		if (!pipe_error(str) || !dquote_error(str) || !squote_error(shell))
			return (ft_putstr_fd("minishell: parsing errore\n", 2), 0);
		i++;
		cmd_t = cmd_t->next;
	}
	return (1);
}
