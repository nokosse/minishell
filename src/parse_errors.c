/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:51:12 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/30 17:06:00 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Returns 0 if there is an unclosed quote.
Unclosed quote is when there is an odd number of quotes.
*/
int	handle_unclosed_quote_err(t_mini *shell)
{
	int i;
	int nb_sq;
	int nb_dq;

	i = 0;
	nb_sq = 0;
	nb_dq = 0;
	while (shell->cmdline[i])
	{
		if (shell->cmdline[i] == '\'')
			nb_sq++;
		if (shell->cmdline[i] == '\"')
			nb_dq++;
		i++;
	}
	if (nb_sq % 2 != 0 || nb_dq % 2 != 0)
	{
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		return (0);
	}
	return (1);
}

/*
This function will handle the input errors.
*/
int	parse_error(t_mini *shell)
{
	if (!handle_unclosed_quote_err(shell))
		return (0);
	free_all(shell);
	return (0);
}
