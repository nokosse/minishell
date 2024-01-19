/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ins_spaces_qtes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:04:51 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/19 10:07:13 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	if (!is_inside_sq(*i, cmd))
	{
		if (cmd[*i] == '\"')
			(*dq)++;
	}
	if (!is_inside_dq(*i, cmd))
	{
		if (cmd[*i] == '\'')
			(*sq)++;
	}
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
		// if (!is_inside_sq(i, shell->cmdline) && is_evn_dq(i, dq, shell))
		// 	write_space(&new, shell->cmdline, &i, &j);
		if (!is_inside_dq(i, shell->cmdline) && is_evn_sq(i, sq, shell))
			write_space(&new, shell->cmdline, &i, &j);
		else
			new[j++] = shell->cmdline[i++];
	}
	free(shell->cmdline);
	shell->cmdline = new;
	return (1);
}
