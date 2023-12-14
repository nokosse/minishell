/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:42:48 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/14 11:45:28 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
'envp' is litteraly all the output you have when you type 'env' in your terminal
We will copy all the envp to out own env, exept if we start with env -i
*/

int	main(int ac, char **av, char **envp)
{
	t_mini				mini;

	mini.env = NULL;
	mini.env = ft_init_env(mini.env, envp);
	if (ac == 1 && mini.env != NULL)
	{
		minishell_loop(&mini);
	}
	return (0);
	(void)av;
}
