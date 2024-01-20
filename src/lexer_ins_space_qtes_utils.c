/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ins_space_qtes_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:27:42 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/20 15:05:26 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Initialize the i, j, dq and sq variables of insert_spaces_quotes() to 0.
*/
void	init_ints(int *i, int *j, int *dq, int *sq)
{
	*i = 0;
	*j = 0;
	*dq = 0;
	*sq = 0;
}

/*
Checks if in the current index, we're inside double quotes.
Returns 1 if we are, 0 if we're not.
*/
int	is_inside_dq(int i, char *str)
{
	int	j;
	int	opened;
	int	closed;

	j = i;
	opened = 0;
	closed = 0;
	while (j >= 0)
	{
		if (str[j] == '\"')
			opened = 1;
		j--;
	}
	j = i;
	while (j < (int)ft_strlen(str))
	{
		if (str[j] == '\"')
			closed = 1;
		j++;
	}
	if (opened && closed)
		return (1);
	return (0);
}

/*
Checks if in the current index, we're inside single quotes.
Returns 1 if we are, 0 if we're not.
*/
int	is_inside_sq(int i, char *str)
{
	int	j;
	int	opened;
	int	closed;

	j = i;
	opened = 0;
	closed = 0;
	while (j >= 0)
	{
		if (str[j] == '\'')
			opened = 1;
		j--;
	}
	j = i;
	while (j < (int)ft_strlen(str))
	{
		if (str[j] == '\'')
			closed = 1;
		j++;
	}
	if (opened && closed)
		return (1);
	return (0);
}

/*
Function to put this 3 line condition into a function to make it 1 line when
calling it in insert_spaces_quotes().

if (shell->cmdline[i] == '\"' && dq % 2 == 0
	&& i + 1 < (int)ft_strlen(shell->cmdline)
	&& shell->cmdline[i + 1] != ' ')
*/
int	is_evn_dq(int i, int dq, t_mini *shell)
{
	if (shell->cmdline[i] == '\"' && dq % 2 == 0
		&& i + 1 < (int)ft_strlen(shell->cmdline)
		&& shell->cmdline[i + 1] != ' ')
	{
		return (1);
	}
	return (0);
}

/*
Function to put this 3 line condition into a function to make it 1 line when
calling it in insert_spaces_quotes().

if (shell->cmdline[i] == '\'' && sq % 2 == 0
	&& i + 1 < (int)ft_strlen(shell->cmdline)
	&& shell->cmdline[i + 1] != ' ')
*/
int	is_evn_sq(int i, int sq, t_mini *shell)
{
	if (shell->cmdline[i] == '\'' && sq % 2 == 0
		&& i + 1 < (int)ft_strlen(shell->cmdline)
		&& shell->cmdline[i + 1] != ' ')
		return (1);
	return (0);
}
