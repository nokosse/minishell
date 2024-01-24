/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:48:10 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/24 13:41:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Return 1 if the [1] argument is '-n'
*/
int	check_n_flag(char **cmd)
{
	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
		return (1);
	return (0);
}

/*
Uses 'ft_putstr_fd' to print to stdout the arguments of 'echo'
Puts a space between each argument with 'ft_putchar_fd'
If echo has the '-n' flag, it will not print a newline at the end.
*/
int	builtin_echo(char **cmd)
{
	int	i;

	i = 1;
	if (check_n_flag(cmd))
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!check_n_flag(cmd))
		ft_putchar_fd('\n', 1);
	g_sig = 0;
	return (0);
}
