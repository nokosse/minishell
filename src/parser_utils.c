/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:34:58 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/03 15:40:42 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function will simply count the number of pipes in the t_lex linked list.
*/
void	count_pipes_and_commands(t_mini *shell)
{
	int		i;
	t_lex	*tmp;

	i = 0;
	shell->nb_pipes = 0;
	shell->nb_commands = 0;
	tmp = shell->lex;
	while (i < shell->nb_tokens)
	{
		if (tmp->token == PIPE)
			shell->nb_pipes++;
		tmp = tmp->next;
		i++;
	}
	shell->nb_commands = shell->nb_pipes + 1;
}
