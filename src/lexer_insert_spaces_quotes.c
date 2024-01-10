/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_insert_spaces_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:04:51 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/10 16:29:56 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		return (1);
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

/*
Writes a space in the new string, and increments i and j.
*/
void	write_space(char **new, char *cmd, int *i, int *j)
{
	(*new)[*j] = cmd[*i];
	(*j)++;
	(*i)++;
	(*new)[*j] = ' ';
	(*j)++;
}

void	count_quotes(int *dq, int *sq, char *cmd, int *i)
{
	if (cmd[*i] == '\"')
		(*dq)++;
	if (cmd[*i] == '\'')
		(*sq)++;
}

/*
Insert a space after an even quote, double or simple.
*/
int	insert_spaces_quotes(t_mini *shell)
{
	char		*new;
	static int	dq;
	static int	sq;
	int			i;
	int			j;

	init_ints(&i, &j, &dq, &sq);
	new = ft_calloc(count_len(shell->cmdline) + 1, sizeof(char));
	if (!new)
		return (0);
	while (shell->cmdline[i])
	{
		count_quotes(&dq, &sq, shell->cmdline, &i);
		if (is_evn_dq(i, dq, shell))
			write_space(&new, shell->cmdline, &i, &j);
		else if (is_evn_sq(i, sq, shell))
			write_space(&new, shell->cmdline, &i, &j);
		else
			new[j++] = shell->cmdline[i++];
	}
	free(shell->cmdline);
	shell->cmdline = new;
	return (1);
}
