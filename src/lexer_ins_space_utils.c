/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ins_space_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:42:29 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/18 11:04:32 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Returns 1 if the double quote is closed, 0 if not.
*/
int	dq_is_closed(char *cmd, int i)
{
	int	j;

	j = i;
	j++;
	while (cmd[j] && cmd[j] != '\"')
		j++;
	if (cmd[j] == '\"')
		return (1);
	return (0);
}

/*
Returns 1 if the simple quote is closed, 0 if not.
*/
int	sq_is_closed(char *cmd, int i)
{
	int	j;

	j = i;
	j++;
	while (cmd[j] && cmd[j] != '\'')
		j++;
	if (cmd[j] == '\'')
		return (1);
	return (0);
}

/*
Copies the string from cmd to new from the actual double quote to the next one
but only if the double quote is closed.
*/
void	skip_double_quotes_2strings(char **cmd, char **new, int *i, int *k)
{
	if ((*cmd)[*i] == '\"' && dq_is_closed(*cmd, *i))
	{
		(*new)[*k] = (*cmd)[*i];
		(*i)++;
		(*k)++;
		while ((*cmd)[*i] && (*cmd)[*i] != '\"')
		{
			(*new)[*k] = (*cmd)[*i];
			(*i)++;
			(*k)++;
		}
		if ((*cmd)[*i] == '\"')
		{
			(*new)[*k] = (*cmd)[*i];
			(*k)++;
			(*i)++;
		}
	}
}

/*
Copies the string from str1 to str2 from the actual simple quote to the next one
but only if the simple quote is closed.
*/
void	skip_simple_quotes_2strings(char **cmd, char **new, int *i, int *k)
{
	if ((*cmd)[*i] == '\'' && sq_is_closed(*cmd, *i))
	{
		(*new)[*k] = (*cmd)[*i];
		(*i)++;
		(*k)++;
		while ((*cmd)[*i] && (*cmd)[*i] != '\'')
		{
			(*new)[*k] = (*cmd)[*i];
			(*i)++;
			(*k)++;
		}
		if ((*cmd)[*i] == '\'')
		{
			(*new)[*k] = (*cmd)[*i];
			(*k)++;
			(*i)++;
		}
	}
}
