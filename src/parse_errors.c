/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:51:12 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/20 15:54:06 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_quote(char *str, char c)
{
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		return (1);
	return (0);
}

void	skip_any_quote(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	(*i)++;
}

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

/*
This function will handle the quote errors.
It parses from the raw command line. (str)
*/
int	quote_error(char *str)
{
	int	i;
	int	dq;
	int	sq;

	i = 0;
	while (str[i])
	{
		dq = 0;
		sq = 0;
		if (!handle_sq(str, &i, &sq))
			return (0);
		if (!handle_dq(str, &i, &dq))
			return (0);
		if (dq == 0 && sq == 0)
			i++;
	}
	return (1);
}

/*
This function handle the redirection errors.
It parses with the tokens of lexer.
*/
int	redir_error_lex(t_mini *shell)
{
	t_lex	*lex_t;
	int		i;

	i = 0;
	lex_t = shell->lex;
	while (i < shell->nb_tokens)
	{
		if (lex_t->token != WORD && lex_t->token != PIPE)
		{
			if (i == shell->nb_tokens - 1)
				return (0);
			if (lex_t->next->token != WORD)
				return (0);
		}
		lex_t = lex_t->next;
		i++;
	}
	return (1);
}

/*
We need this function to handle 'wierd' redirection errors
because wierd redirections are not counted as redirection tokens in the lexer.
So we need to parse the raw command to check if any direction is wierd lookuing
like : '>>>' or '><' etc...
*/
int	redir_error_str(char *str)
{
	int	i;
	int	quote;

	i = 0;
	while (str[i])
	{
		quote = 0;
		if (str[i] == '\"' || str[i] == '\'')
		{
			skip_any_quote(str, &i, str[i]);
			quote = 1;
		}
		if ((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			|| (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			|| (str[i] == '>' && str[i + 1] == '<')
			|| (str[i] == '<' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '>')
			|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '<'))
			return (0);
		if (quote == 0)
			i++;
	}
	return (1);
}

/*
This function will handle the input errors.
*/
int	parse_error(t_mini *shell)
{
	t_cmd	*cmd_t;
	char	*str;
	int		i;

	i = 0;
	cmd_t = shell->cmd;
	while (i < shell->nb_commands)
	{
		str = cmd_t->str;
		if (!quote_error(str) || !redir_error_str(str))
			return (ft_putstr_fd("minishell: parsing error\n", 2), 0);
		i++;
		cmd_t = cmd_t->next;
	}
	if (!redir_error_lex(shell))
		return (ft_putstr_fd("minishell: parsing error\n", 2), 0);
	return (1);
}
