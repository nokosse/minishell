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
	if (str[*(i + 1)] == '<')
	{
		(*cmd)->dir->left = 1;
		(*cmd)->dir->r_double = 1;
		i += 2;
		return (1);
	}
	else if (is_valid_char(str[*(i + 1)]))
	{
		(*cmd)->dir->left = 1;
		i += 1;
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

void	set_bool_file(t_cmd **cmd)
{
	if ((*cmd)->bool_file == 1)
	{
		(*cmd)->dir->next = ft_dirnew(cmd);
		(*cmd)->dir = (*cmd)->dir->next;
	}
	else
	{
		(*cmd)->bool_file = 1;
		(*cmd)->dir = ft_dirnew(cmd);
	}

}

int	handle_redirection(t_cmd **cmd, char *str, int *i, int print)
{
	char	c;
	int		j;

	j = 0;
	if (is_valid_dir(cmd, str, i) && is_valid_char(str[*i]))
	{
		while (str[*i] && is_whitespace(str[*i]))
			*i += 1;
		if (is_quote(str, *i, str[*i]))
			c = str[*i];
		else
			c = '|';
		while (str[*i + j] && !(is_whitespace(str[*i + j])) && str[*i + j] != c)
			j++;
		if (print)
			(*cmd)->dir->content = word_to_array(str, *i, j, cmd);
		*i += j;
		return (1);
	}
	return (0);

}
