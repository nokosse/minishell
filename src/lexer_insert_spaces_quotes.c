/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_insert_spaces_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:04:51 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/10 14:05:27 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_ints(int *i, int *j, int *dq, int *sq)
{
	*i = 0;
	*j = 0;
	*dq = 0;
	*sq = 0;
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
		if (shell->cmdline[i] == '\"')
			dq++;
		if (shell->cmdline[i] == '\'')
			sq++;
		if (shell->cmdline[i] == '\"' && dq % 2 == 0
			&& i + 1 < (int)ft_strlen(shell->cmdline)
			&& shell->cmdline[i + 1] != ' ')
		{
			new[j++] = shell->cmdline[i++];
			new[j++] = ' ';
		}
		else if (shell->cmdline[i] == '\'' && sq % 2 == 0
			&& i + 1 < (int)ft_strlen(shell->cmdline)
			&& shell->cmdline[i + 1] != ' ')
		{
			new[j++] = shell->cmdline[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = shell->cmdline[i++];
	}
	free(shell->cmdline);
	shell->cmdline = new;
	return (1);
}
