/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:51:12 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/01 14:42:19 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		if (ft_strlen(lex_t->word) >= 2 && ft_strchr(lex_t->word, '|'))
			return (0);
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
		return (ft_putstr_fd("parsing error: pipe error\n", 2), 0);
	return (1);
}
