/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:16:46 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/26 13:22:34 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
These are 'junk' characters that returns a parsing error if they are not
between quotes.
*/
int	is_junk_char(char c)
{
	if (c == '\\' || c == '*' || c == ';' || c == '&'
		|| c == '(' || c == ')' || c == '\0')
		return (1);
	return (0);
}

/*
This function will return 1 if str is a closed quote.
*/
int	is_quote(char *str, char c)
{
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		return (1);
	return (0);
}

/*
This function will increment i through the specified quote.
Starting from the first quote, landing after the closing one.
*/
void	skip_any_quote(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	(*i)++;
}

/*
This function will increment i if str[i] is a closed single quote.
Will also set sq flag to 1.
*/
int	handle_sq(char *str, int *i, int *sq)
{
	if (str[*i] == '\'')
	{
		if (sq_is_closed(str, *i))
		{
			*sq = 1;
			skip_any_quote(str, i, '\'');
		}
		else
			return (0);
	}
	return (1);
}

/*
This function will increment i if str[i] is a closed double quote.
Will also set dq flag to 1.
*/
int	handle_dq(char *str, int *i, int *dq)
{
	if (str[*i] == '\"')
	{
		if (dq_is_closed(str, *i))
		{
			*dq = 1;
			skip_any_quote(str, i, '\"');
		}
		else
			return (0);
	}
	return (1);
}
