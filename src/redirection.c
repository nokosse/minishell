/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:53:18 by operez            #+#    #+#             */
/*   Updated: 2023/06/15 12:10:47 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_bool_file(t_cmd **cmd)
{
	t_dir	*tmp;
	t_cmd	*copy;

	copy = *cmd;
	if (copy->bool_file == 1)
	{
		tmp = copy->dir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_dirnew(cmd);
		copy->bool_file = 1;
	}
	else
	{
		copy->bool_file = 1;
		copy->dir = ft_dirnew(cmd);
	}
}

int	handle_right(t_cmd **cmd, char *str, int i)
{
	t_cmd	*tmp;
	t_dir	*dir;

	set_bool_file(cmd);
	tmp = *cmd;
	if (str[i + 1] == '>')
	{
		dir = ft_dirlast(tmp->dir);
		dir->right= 1;
		dir->type= 2;
		return (2);
	}
	else if (is_valid_char(str[i + 1]))
	{
		dir = ft_dirlast(tmp->dir);
		dir->right= 1;
		dir->type= 1;
		return (1);
	}
	return (0);
}

int	handle_left(t_cmd **cmd, char *str, int i)
{
	t_cmd	*tmp;
	t_dir	*dir;

	set_bool_file(cmd);
	tmp = *cmd;
	if (str[i + 1] == '<')
	{
		dir = ft_dirlast(tmp->dir);
		dir->left = 1;
		dir->type= 2;
		return (2);
	}
	else if (is_valid_char(str[i + 1]))
	{
		dir = ft_dirlast(tmp->dir);
		dir->left = 1;
		dir->type= 1;
		return (1);
	}
	return (0);
}

int	is_valid_dir(char *str, int i)
{
	if (str[i] == '<')
	{
		if (str[i + 1] == '<' || is_valid_char(str[i + 1]))
			return (1);
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>' || is_valid_char(str[i + 1]))
			return (1);
	}
	return (0);
}


void	handle_dir(t_cmd **cmd, char *str, int i)
{
	if (str[i] == '<')
		handle_left(cmd, str, i);
	if (str[i] == '>')
		handle_right(cmd, str, i);
}

void	string_to_filename(t_cmd **cmd, char *str, int i, int j)
{
	t_dir	*print;

	print = (*cmd)->dir;
	while (print && print->content)
		print = print->next;
	print->content = word_to_array(str, i, j, cmd);
}

void	move_thrgh_redir(t_cmd **cmd, char *str, int *i, int print)
{
	char	c;
	int		j;

	j = 0;
	c = 0;
	while (str[*i] && is_whitespace(str[*i]))
		*i += 1;
	if (is_quote(str, *i, str[*i]))
	{
		c = str[*i];
		while (str[*i + 1 + j] != c)
			j++;
		if (print)
			string_to_filename(cmd, str, *i, j + 1);
		*i += j + 2;
	}
	else 
	{
		while (str[*i + j] && !(is_whitespace(str[*i + j])) && str[*i + j] != '>'
			&& str[*i + j] != '<' && str[*i + j] != '|')
			j++;
		if (print)
			string_to_filename(cmd, str, *i, j);
		*i += j;
	}
}
