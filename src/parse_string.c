/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:40:07 by operez            #+#    #+#             */
/*   Updated: 2023/06/15 13:23:41 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
int	check_var(char *str, int *i, char c)
{

}
*/
int	check_redir(char *str, int *i, char c)
{
	if (str[*i + 1] == '\0')
	{
		ft_printf("parse error near '\n''");
		return (0);
	}
	if (!is_valid_char(str[*i + 1]))
	{
		ft_printf("parse error near '%c'\n", str[*i + 1]);
		return (0);
	}
	if ((str[*i] == '<' && str[*i + 1] == '>') || (str[*i] == '>' && str[*i + 1] == '<'))
	{
		ft_printf("parse error near '%c'\n", str[*i + 1]);
		return (0);
	}
	if (str[*i + 1] == c)
	{
		if (!is_valid_char(str[*i + 2]) || str[*i + 2] == '|'
				|| str[*i + 2] == '<' || str[*i + 2] == '>')
		{
			ft_printf("parse error near '%c'\n", str[*i + 1]);
			return (0);
		}
		else
			*i += 1;
	}
	*i += 1;
	return (1);
}

int	check_string(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '|')
	{
		ft_printf("parse error near '|'\n");
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '|')
		{
			while (str[i + j] && is_whitespace(str[i + j]))
				j++;
			if (str[i + j] == '|' && j != 0)
			{
				ft_printf("parse error near '|'\n");
				return (0);
			}
			j = 0;
		}
		if (is_quote(str, i, str[i]))
		{
			i = move_through_quote(str, i, str[i]);
			i++;
			continue ;
		}
		if (!is_valid_char(str[i]))
		{
			ft_printf("parse error near '%c'\n", str[i]);
			return (0);
		}
		if (str[i] == '<' || str[i] == '>')
		{
			if (!check_redir(str, &i, str[i]))
				return (0);
			continue ;
		}
		i++;
	}
	return (1);
}
