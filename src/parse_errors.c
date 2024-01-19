/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:51:12 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/19 11:45:07 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_quote(char *str, char c)
{
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		return (1);
	return (0);
}

/*
Handle pipe parsing errors :
'ls || wc' , 'ls | | wc', 'ls |' , '| ls'
'ls |wdwwd' , 'ls| wc' , 'ls|wc'
(for the 3 last ones,  I may have wrote a better lexer that allows this since
this function was written)
*/
int	handle_pipe_err2(t_mini *shell)
{
	t_lex	*lex_t;
	int		i;

	i = 0;
	lex_t = shell->lex;
	while (i < shell->nb_tokens)
	{
		if (lex_t->token == PIPE && i == 0)
			return (0);
		if (lex_t->token == PIPE && lex_t->next->token == PIPE)
			return (0);
		if (lex_t->word[0] == '|' && lex_t->word[1] != '\0')
			return (0);
		if (ft_strlen(lex_t->word) >= 2 && ft_strchr(lex_t->word, '|')
			&& !is_quote(lex_t->word, '\"') && !is_quote(lex_t->word, '\''))
			return (0);
		lex_t = lex_t->next;
		i++;
	}
	return (1);
}

/*
Thie function will handle the misplacement of the redirections.
It will hendle the following errors :
- redirection is the first token
- redirection is the last token
- redirection is not followed by a WORD token
*/
int	handle_redir_err(t_mini *shell)
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
The main difference with handle_redir_err is that this one will handle
'WORDS' tokens that looks like this : '>>>>' , '<><>' etc..
*/
int	handle_wierd_redir_err(t_mini *shell)
{
	t_lex	*lex_t;
	int		i;

	i = 0;
	lex_t = shell->lex;
	while (i < shell->nb_tokens)
	{
		if (lex_t->token == WORD)
		{
			if ((lex_t->word[0] == '<' || lex_t->word[0] == '>')
				&& (ft_strlen(lex_t->word) > 2))
				return (0);
			if (lex_t->word[0] == '<' || lex_t->word[1] == '>')
				return (0);
			if (lex_t->word[0] == '>' && lex_t->word[1] == '<')
				return (0);
		}
		lex_t = lex_t->next;
		i++;
	}
	return (1);
}

/*
This function will handle the input errors.
*/
int	parse_error(t_mini *shell)
{
	if (!handle_pipe_err2(shell))
		return (ft_putstr_fd("minishell: parsing error\n", 2), 0);
	if (!handle_redir_err(shell))
		return (ft_putstr_fd("minishell: parsing error\n", 2), 0);
	if (!handle_wierd_redir_err(shell))
		return (ft_putstr_fd("minishell: parsing error\n", 2), 0);
	if (!handle_unclosed_quote_err(shell->cmdline))
		return (ft_putstr_fd("minishell: parsing error\n", 2), 0);
	return (1);
}
