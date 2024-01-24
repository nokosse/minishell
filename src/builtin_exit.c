/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:47:55 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/24 13:41:29 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Count the number of arrays in cmd
*/
int	exit_count_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
		ft_putstr_fd("exit: too many arguments\n", 2);
	return (i);
}

/*
'exit' will exit the minishell with the exit code you want, 0 by default.
*/
void	builtin_exit(t_mini *shell, char **cmd)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	if (exit_count_args(cmd) > 2)
		exit_code = 1;
	else if (cmd[1])
	{
		i = ft_atoi(cmd[1]);
		if (i != 0)
		{
			if (i > 254)
				exit_code = i % 256;
			else
				exit_code = i;
		}
		else
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit_code = 2;
		}
	}
	rl_clear_history();
	free_all(shell);
	exit(exit_code);
}
