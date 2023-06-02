/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:53:18 by operez            #+#    #+#             */
/*   Updated: 2023/06/02 14:27:14 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_right(t_cmd **cmd, char *str, int *i)
{
	if (str[*i + 1] == '>')
	{
		(*cmd)->dir->right = 1;
		(*cmd)->dir->r_double = 1;
		*i += 2;
		return (1);
	}
	else if (is_valid_char(str[*i + 1]))
	{
		(*cmd)->dir->right = 1;
		*i += 1;
		return (1);
	}
	return (0);
}

int	handle_left(t_cmd **cmd, char *str, int *i)
{
	if (str[*i + 1] == '<')
	{
		(*cmd)->dir->left = 1;
		(*cmd)->dir->r_double = 1;
		*i += 2;
		return (1);
	}
	else if (is_valid_char(str[*i + 1]))
	{
		(*cmd)->dir->left = 1;
		*i += 1;
		return (1);
	}
	return (0);
}

int	is_valid_dir(t_cmd **cmd, char *str, int *i)
{
	if (str[*i] == '<')
	{
		if (handle_left(cmd, str, i))
			return (1);
	}
	else if (str[*i] == '>')
	{
		if (handle_right(cmd, str, i))
			return (1);
	}
	return (0);
}

int	handle_redirection(t_cmd **cmd, char *str, int *i)
{
	int		j;
	char	c;

	if (is_valid_dir(cmd, str, i) && is_valid_char(str[*i]))
	{
		if ((*cmd)->bool_file == 1)
		{
			(*cmd)->dir->next = ft_dirnew(cmd);
			(*cmd)->dir = (*cmd)->dir->next;
		}
		while (str[*i] && is_whitespace(str[*i]))
			i++;
		if ((str[*i] == '\'' || str[*i] == '\"') && is_quote(str, *i, str[*i]))
			c = str[*i];
		else
			c = '|';
		while (str[*i + j] && !(is_whitespace(str[*i + j])) && str[*i + j + 1] != c)
			j++;
		(*cmd)->dir->content = word_to_array(str, *i, j);
		*i = j;
		return (1);
	}
	return (0);
}
