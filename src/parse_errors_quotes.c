/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:34:25 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/12 14:34:49 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Returns 1 if it finds a double quote that close the current double quote.
Ignore the escaped double quotes (\)
*/
int	is_dq_closed(char *str, int *i)
{
	int	j;

	j = *i + 1;
	while (str[j])
	{
		if (str[j] == '\"' && str[j - 1] != '\\')
		{
			*i = j;
			return (1);
		}
		j++;
	}
	return (0);
}

/*
Returns 1 if it finds a single quote that close the current single quote.
Ignore the escaped single quotes (\)
*/
int	is_sq_closed(char *str, int *i)
{
	int	j;

	j = *i + 1;
	while (str[j])
	{
		if (str[j] == '\'' && str[j - 1] != '\\')
		{
			*i = j;
			return (1);
		}
		j++;
	}
	return (0);
}

/*
This function will handle the unclosed quotes errors.
*/
int	handle_unclosed_quote_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !is_dq_closed(str, &i))
		{
			return (0);
		}
		if (str[i] == '\'' && !is_sq_closed(str, &i))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
