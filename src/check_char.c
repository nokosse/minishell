/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:51:40 by operez            #+#    #+#             */
/*   Updated: 2023/06/15 17:40:50 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
			|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_valid_char(char c)
{
	if (c == '\0')
		return (0);
	if ( c == '\\' || c == ':' || c == '*' || c == '?' || c == ';'
			|| c == '&' || c == '(' || c == ')'
			|| c == '$' || c == '!')
		return (0);
	return (1);
}

int	is_bracket(char *str, int i, char c)
{
	if (c == '{')
	{
		while (str[++i])
		{
			if (str[i] == '}')
				return (1);
		}
	}
	return (0);
}

int	is_quote(char *str, int i, char c)
{
	if (c == '\'' || c == '\"')
	{
		while (str[++i])
		{
			if (str[i] == c)
			{
				if (str[i] == '\'')
					return (1);
				if (str[i] == '\"')
					return (2);
			}
		}
	}
	return (0);
}
