/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:19:51 by operez            #+#    #+#             */
/*   Updated: 2023/06/02 15:09:47 by operez           ###   ########.fr       */
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
//		ft_printf("Nbr de Tokens = %d\n", tmp->tokens_count);
		tmp->tokens = malloc (sizeof(char *) * ((tmp->tokens_count) + 1));
		if (!tmp->tokens)
			end(cmd);
		tmp->tokens[tmp->tokens_count] = 0;
		tmp = tmp->next;
	}
}

char	*word_to_array(char *str, int i, int j, t_cmd **cmd)
{
	int		k;
	char	*tokens;

	if (str)
	{
		k = 0;
		if ((str[i] == '\'' || str[i] == '\"') && str[i] == str[i + j])
		{
			i++;
			j -= 1;
		}
		tokens = malloc (sizeof(char) * (j + 1));
//		ft_printf("Nbr de char alloue = %d\n", sizeof(char) * (j + 1));
		if (!tokens)
			end(cmd);
		while (str[i] && k < j)
			tokens[k++] = str[i++];
		tokens[k] = '\0';
	}
	return (tokens);
}

void	get_token(char *str, t_cmd **cmd)
{
	int		i;
	int		j;
	int		k;
	char	quote;
	t_cmd	*save;

	i = 0;
	k = 0;
	save = *cmd;
	while (str[i])
	{
		j = 0;
		while (str[i] && is_whitespace(str[i]))
			i++;
		if (is_quote(str, i, str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && is_whitespace(str[i]))
				i++;
			while (str[i + j] && str[i + j] != quote)
				j++;
			(*cmd)->tokens[k++] = word_to_array(str, i, j, cmd);
			i = i + j + 1;
			continue ;
		}
		if (str[i] == '|')
		{
			k = 0;
			*cmd = (*cmd)->next;
			i++;
			continue ;
		}
		if (str[i] == '<' || str[i] == '>')
		{
			set_bool_file(cmd);
			handle_redirection(cmd, str, &i, 1);
		}
		while (str[i + j] && !(is_whitespace(str[i + j])) && str[i + j] != '|')
			j++;
		if (str[i] != '\0')
			(*cmd)->tokens[k++] = word_to_array(str, i, j, cmd);
		i += j;
	}
	*cmd = save;
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
			if (str[i] == '<' || str[i] == '>')
			{
				handle_redirection(cmd, str, &i, 0);
				break ;
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
		executor(cmd->tokens, envp);
		free_struct(&cmd);
	}
}
