/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:48:26 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/20 17:01:10 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Simply print the result of getcwd() to stdout.
Set the signal to 0 as a success command.
*/
void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}
	g_sig = 0;
}
