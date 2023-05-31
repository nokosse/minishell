/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:19:51 by operez            #+#    #+#             */
/*   Updated: 2023/05/31 16:47:58 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	create_lst(char *str, t_cmd **cmd)
{
	t_cmd	*tmp;
	char	**cmd_nbr;
	int	i;

	i = 0;
	*cmd = ft_commandnew();
	tmp = *cmd;
	cmd_nbr = ft_split(str, '|');
	while (cmd_nbr[i])
		i++;
	//ft_printf("Number of commands = %d\n", i);
	while (i > 1)
	{
		tmp->next = ft_commandnew();
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
		//ft_printf("tokens_count = %d\n", tmp->tokens_count);
		tmp->tokens = malloc (sizeof(char *) * ((tmp->tokens_count) + 1));
		if (!tmp->tokens)
			end();
		tmp->tokens[tmp->tokens_count] = 0;
		tmp = tmp->next;
	}
}

char	*word_to_array(char *str, int i, int j)
{
	int		k;
	char	*tokens;

	k = 0;
	tokens = malloc (sizeof(char) * (j + 1));
	if (!tokens)
		end();
	while (k <= j)
		tokens[k++] = str[i++];
	tokens[k] = '\0';
	return (tokens);
}

void	get_token(char *str, t_cmd **cmd)
{
	int	i;
	int	j;
	int	k;
	t_cmd	*save;

	i = 0;
	k = 0;
	save = *cmd;
	while (str[i])
	{
		j = 0;
		while (str[i] && is_whitespace(str[i]))
			i++;
		if (str[i] == '|')
		{
			k = 0;
			*cmd = (*cmd)->next;
			i++;
			continue ;
		}
		if (str[i] == '<' || str[i] == '>')
			handle_redirection(cmd, str, &i);
		while (str[i + j] && !(is_whitespace(str[i + j])) && str[i + j + 1] != '|')
			j++;
		if (str[i] != '\0')
			(*cmd)->tokens[k++] = word_to_array(str, i, j);
		while (str[i] && !(is_whitespace(str[i])))
			i++;
	}
	*cmd = save;
}

void	tokens_count(char *str, t_cmd **cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = *cmd;
	while (str[i])
	{
		while (str[i] && is_whitespace(str[i]))
			i++;
		if (str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>')
			tmp->tokens_count++;
		while (str[i] && !(is_whitespace(str[i])))
		{
			if (str[i] == '|')
			{
				i++;
				tmp = tmp->next;
				break ;
			}
			/*
			if (str[i] == '<' || str[i] == '>')
				ignore_param(cmd, str, &i);
			//creer fonction qui va ignorer la creation d un token si chevron present
			//voir a deplacer handle_redir ici a la place
				*/
			i++;
		}
	}
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
		executor(cmd->tokens, envp);
	}
	else 
		end();
}
