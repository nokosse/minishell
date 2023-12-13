/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:42:48 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/13 11:52:48 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
'envp' is litteraly all the output you have when you type 'env' in your terminal
We will copy all the envp to out own env.
But if we start minishell like this : env -i ./minishell
Then we will have to create a clean env with only PWD, SHLVL and _.
- PWD is the current directory, nothing new
- SHLVL is the current level of the shell, SH for shell, lvl for level..
1 by default, incremented by 1 each time you start a new shell.
- _ (underscore) is 
*/

int	main(int ac, char **av, char **envp)
{
	char	**env;

	env = NULL;
	ft_init(env, envp);
	if (ac == 1)
	{
		printf("welcome to minishell\n");
	}
	return (0);
	(void)ac;
	(void)av;
	(void)envp;
}
