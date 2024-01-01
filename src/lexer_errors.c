/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:54:06 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/01 13:17:01 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Returns 0 if the pipe is the last token.
*/
int	handle_pipe_err1(t_mini *shell)
{
	t_lex	*lex_t;
	int		i;

	i = 0;
	lex_t = shell->lex;
	while (i < shell->nb_tokens)
	{
		if (lex_t->token == PIPE && lex_t->i == shell->nb_tokens - 1)
			return (0);
		lex_t = lex_t->next;
		i++;
	}
	return (1);
}

/*
Handle errors with tokens that can segfault the parser.
*/
int	lexer_error(t_mini *shell)
{
	if (!handle_pipe_err1(shell))
		return (ft_putstr_fd("parsing error: pipe error\n", 2), 0);
	return (1);
}
