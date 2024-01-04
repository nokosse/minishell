/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:42:48 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/04 16:19:15 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
It's the one global variable we will use in minishell.
It's mainly used to define exit codes.
*/

int	g_sig;

/*
'envp' is litteraly all the output you have when you type 'env' in your terminal
We will copy all the envp to out own env, exept if we start with env -i
*/

int	main(int ac, char **av, char **envp)
{
	t_mini				mini;

	mini.env = NULL;
	mini.env = ft_init_env(mini.env, envp);
	if (ac == 1 && mini.env != NULL && av[0] != NULL)
	{
		minishell_loop(&mini);
	}
	return (0);
}
