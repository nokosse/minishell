/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:19:51 by operez            #+#    #+#             */
/*   Updated: 2023/06/15 17:46:59 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_lst(char *str, t_cmd **cmd)
{
	t_cmd	*tmp;
	char	**cmd_nbr;
	int	i;

	i = 0;
	*cmd = ft_commandnew();
	if (!(*cmd))
		end(cmd);
	tmp = *cmd;
	cmd_nbr = ft_split(str, '|');
	while (cmd_nbr[i])
		i++;
	while (i > 1)
	{
		tmp->next = ft_commandnew();
		if (!tmp->next)
			end(cmd);
		tmp = tmp->next; 
		i--;
	}
}

void	malloc_tokens_table(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		tmp->tokens = malloc (sizeof(char *) * ((tmp->tokens_count) + 1));
		if (!tmp->tokens)
			end(cmd);
		tmp->tokens[tmp->tokens_count] = 0;
		tmp = tmp->next;
	}
}

void	get_token(char *str, t_cmd **cmd)
{
	int		i;
	int		j;
	int		k;
	char	c;
	t_cmd	*tmp;
	t_dir	*copy;

	i = 0;
	k = 0;
	tmp = *cmd;
	copy = (*cmd)->dir;
	while (str[i])
	{
		j = 0;
		while (str[i] && is_whitespace(str[i]))
			i++;
		if (is_quote(str, i, str[i]))
		{
			c = str[i];
			while (str[i + 1 + j] != c)
				j++;
			tmp->tokens[k++] = word_to_array(str, i, j + 1, &tmp);
			i += j + 2;
			continue ;
		}
		while (str[i + j] && !(is_whitespace(str[i + j])) && str[i + j] != '|'
				&& str[i + j] != '<' && str[i + j] != '>')
			j++;
		if (j)
			tmp->tokens[k++] = word_to_array(str, i, j, &tmp);
		i += j;
		j = 0;
		if (str[i] == '|')
		{
			k = 0;
			tmp = tmp->next;
			i++;
			continue ;
		}
		if ((str[i] == '<' || str[i] == '>') && is_valid_dir(str, i))
		{
			i += copy->type;
			copy = copy->next;
			move_thrgh_redir(&tmp, str, &i, 1);
		}
	}
}

int	tokens_count(char *str, t_cmd **cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = *cmd;
	while (str[i])
	{
		while (str[i] && is_whitespace(str[i]))
			i++;
		if (is_valid_char(str[i]) && str[i] != '|' && str[i] != '>'
				&& str[i] != '<')
			tmp->tokens_count++;
		while (str[i] && !(is_whitespace(str[i])))
		{
			if (is_quote(str, i, str[i]))
			{
				i = move_through_quote(str, i, str[i]);
				i++;
				break ;
			}
			if (str[i] == '|')
			{
				i++;
				tmp = tmp->next;
				break ;
			}
			if ((str[i] == '<' || str[i] == '>') && is_valid_dir(str, i))
			{
				handle_dir(&tmp, str, i);
				i += ft_dirlast(tmp->dir)->type;
				move_thrgh_redir(&tmp, str, &i, 0);
				break ;
			}
			if (str[i] == '$')
			{
				if (is_bracket(str, i, str[i]))
				{
					ft_printf("do something\n");
				}
			}
			i++;
		}
	}
	return (1);
}

void	lexer(char *str, char **envp)
{
	t_cmd	*cmd;

	if (str && check_string(str))
	{
		create_lst(str, &cmd);
		tokens_count(str, &cmd);
		malloc_tokens_table(&cmd);
		get_token(str, &cmd);
		ft_print(cmd);
		executor(cmd, envp);
		free_struct(&cmd);
	}
}
