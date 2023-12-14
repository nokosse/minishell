/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:42:48 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/14 10:01:32 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
'envp' is litteraly all the output you have when you type 'env' in your terminal
We will copy all the envp to out own env.
But if we start minishell like this : env -i ./minishell
Then we will have to create a clean env with only PWD, SHLVL and _.
*/

int	main(int ac, char **av, char **envp)
{
	char	**env;

	env = NULL;
	env = ft_init_env(env, envp);
	if (ac == 1 && env != NULL)
	{
		int i = 0;
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
	return (0);
	(void)ac;
	(void)av;
	(void)envp;
}
