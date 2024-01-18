/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_count_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:48:54 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/18 14:50:30 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	skip_quotes(char **cmd, int *i, char quote)
{
	(*i)++;
	while ((*cmd)[*i] != quote)
		(*i)++;
	(*i)++;
}

/*
This function will count the number of tokens in the command line.
It will loop the command line and increment 'nb_tokens' each time it finds a
space.
*/
int	count_tokens(char *cmdl)
{
	int		i;
	int		nb_tokens;

	i = 0;
	nb_tokens = 0;
	printf("cmdl: %s\n", cmdl);
	while (cmdl[i])
	{
		if (cmdl[i] != ' ')
		{
			nb_tokens++;
			while (cmdl[i] && cmdl[i] != ' ')
			{
				if (cmdl[i] == '\"' && (is_quote_closed(cmdl, i, '\"')))
					skip_quotes(&cmdl, &i, '\"');
				else if (cmdl[i] == '\'' && (is_quote_closed(cmdl, i, '\'')))
					skip_quotes(&cmdl, &i, '\'');
				else
					i++;
			}
		}
		else
			i++;
	}
	return (nb_tokens);
}
