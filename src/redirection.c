/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:53:18 by operez            #+#    #+#             */
/*   Updated: 2023/06/13 17:26:18 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_right(t_cmd **cmd, char *str, int *i)
{
	t_cmd	*tmp;
	t_dir	*dir;

	tmp = ft_cmdlast(*cmd);
	dir = ft_dirlast(tmp->dir);
	if (str[*i + 1] == '>')
	{
		dir->right= 1;
		dir->r_double = 1;
		*i += 2;
		return (1);
	}
	else if (is_valid_char(str[*i + 1]))
	{
		dir->right= 1;
		*i += 1;
		return (1);
	}
	return (0);
}

int	handle_left(t_cmd **cmd, char *str, int *i)
{
	t_cmd	*tmp;
	t_dir	*dir;

	tmp = ft_cmdlast(*cmd);
	dir = ft_dirlast(tmp->dir);
	if (str[*(i + 1)] == '<')
	{
		dir->left = 1;
		dir->r_double = 1;
		*i += 2;
		return (1);
	}
	else if (is_valid_char(str[*(i + 1)]))
	{
		dir->left = 1;
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

void	set_bool_file(t_cmd **cmd)
{
	t_dir	*tmp;
	t_cmd	*copy;

	copy = *cmd;
	if (copy->bool_file == 1)
	{
		ft_printf("bool_file = 1\n");
		tmp = copy->dir;
		while (tmp->next)
			tmp = tmp->next;
		tmp = ft_dirnew(&copy);
		copy->bool_file = 1;
	}
	else
	{
		copy->bool_file = 1;
		copy->dir = ft_dirnew(&copy);
	}
}

int	handle_redirection(t_cmd **cmd, char *str, int *i, int print)
{
	char	c;
	int		j;

	j = 0;
	while (str[*i] && is_whitespace(str[*i]))
		*i += 1;
	if (is_quote(str, *i, str[*i]))
		c = str[*i];
	else
		c = '|';
	while (str[*i + j] && !(is_whitespace(str[*i + j])) && str[*i + j] != c
		&& str[*i + j] != '>' && str[*i + j] != '<')
		j++;
	if (print)
		(*cmd)->dir->content = word_to_array(str, *i, j, cmd);
	if (str[*i + j] == str[*i] && (str[*i] == '\'' || str[*i] == '\"'))
		j++;
	*i += j;
	return (0);
}
