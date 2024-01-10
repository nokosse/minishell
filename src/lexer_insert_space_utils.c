/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_insert_space_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:42:29 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/10 15:42:37 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Skip from the actual quote to the next one.
Increments i and k.
Works for double quotes.
*/
void	skip_double_quotes_2strings(char *str1, char *str2, int *i, int *k)
{
	int	j;
	int	n;

	j = 0;
	n = 0;
	if (str1[*i] == '\"')
	{
		j = *i;
		n = *k;
		str2[n] = str1[j];
		j++;
		n++;
		while (str1[j] && str1[j] != '\"')
		{
			str2[n] = str1[j];
			j++;
			n++;
		}
		if (str1[j] == '\"')
		{
			str2[n] = str1[j];
			j++;
			n++;
		}
	}
}

/*
Skip from the actual quote to the next one.
Increments i and k.
Works for simple quotes.
*/
void	skip_simple_quotes_2strings(char *str1, char *str2, int *i, int *k)
{
	int	j;
	int	n;

	j = 0;
	n = 0;
	if (str1[*i] == '\'')
	{
		j = *i;
		n = *k;
		str2[n] = str1[j];
		j++;
		n++;
		while (str1[j] && str1[j] != '\'')
		{
			str2[n] = str1[j];
			j++;
			n++;
		}
		if (str1[j] == '\'')
		{
			str2[n] = str1[j];
			j++;
			n++;
		}
	}
}
