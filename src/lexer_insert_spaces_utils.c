/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_insert_spaces_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:34:16 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/05 16:35:32 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Skip from the actual quote to the next one. (It's built for 'count_len')
Increment i.
*/
void	skip_quotes_count_len(char *str, int *i)
{
	int	j;

	j = 0;
	if (str[*i] == '\"')
	{
		j = *i;
		j++;
		while (str[j] && str[j] != '\"')
			j++;
		if (str[j] == '\"')
			*i = j;
	}
	if (str[*i] == '\'')
	{
		j = *i;
		j++;
		while (str[j] && str[j] != '\'')
			j++;
		if (str[j] == '\'')
			*i = j;
	}
}

/*
Just skip from the actual quote to the next one. (for ")
Increment i and j.
It's built for 'insert_spaces'.
*/
void	skip_quotes_insert_spaces1(char *str, char *new, int *i, int *j)
{
	int	k;
	int	n;

	k = 0;
	n = 0;
	if (str[*i] == '\"')
	{
		k = *i;
		n = *j;
		new[n] = str[k];
		k++;
		n++;
		while (str[k] && str[k] != '\"')
		{
			new[n] = str[k];
			k++;
			n++;
		}
		if (str[k] == '\"')
		{
			new[n] = str[k];
			*i = k;
			*j = n;
		}
	}	
}

/*
Same but for '.
*/
void	skip_quotes_insert_spaces2(char *str, char *new, int *i, int *j)
{
	int	k;
	int	n;

	k = 0;
	n = 0;
	if (str[*i] == '\'')
	{
		k = *i;
		n = *j;
		new[n] = str[k];
		k++;
		n++;
		while (str[k] && str[k] != '\'')
		{
			new[n] = str[k];
			k++;
			n++;
		}
		if (str[k] == '\'')
		{
			new[n] = str[k];
			*i = k;
			*j = n;
		}
	}	
}
