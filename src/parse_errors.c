/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:51:12 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/29 18:35:58 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Returns 0 if it finds any double/simple not closed quotes.
Just count the number of double quotes in nb_dq.
Then count the number of simple quotes in nb_sq.
Then, if one of then is odd, returns 0, else returns 1.
*/
int	handle_quote_errors(t_mini *shell)
{
	int		i;
	int		nb_dq;
	int		nb_sq;

	i = 0;
	nb_dq = 0;
	nb_sq = 0;
	while (shell->cmdline[i])
	{
		if (shell->cmdline[i] == '"')
			nb_dq++;
		if (shell->cmdline[i] == '\'')
			nb_sq++;
		i++;
	}
	if (nb_dq % 2 != 0 || nb_sq % 2 != 0)
	{
		ft_putstr_fd("minishell should not interpret unclosed quotes", 2);
		ft_putstr_fd(" (PAGE 6)\n", 2);
		return (0);
	}
	return (1);
}

/*
This function will handle the input errors.
*/
int	parse_error(t_mini *shell)
{
	if (handle_quote_errors(shell))
		return (0);
	free_all(shell);
	return (0);
}
