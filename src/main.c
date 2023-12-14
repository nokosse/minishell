/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:42:48 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/14 10:45:24 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This is the loop where we will be able to type commands in our minishell.
The loop will go trough the lexer, if it doesn't fail, it will go through the
parser, if it doesn't fail, it will go through the executor. If something fails
we will print an error just like in bash.
*/
void	minishell_loop(char ***env)
{
	char	*cmdline;

	cmdline = NULL;
	while (1)
	{
		cmdline = readline("minishell$> ");
		if (!cmdline)
		{
			handle_readline_error(*env, cmdline);
			break ;
		}
		if (!ft_strlen(cmdline))
		{
			free(cmdline);
			continue ;
		}
		
	}
	(void)env;
}

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
		minishell_loop(&env);
	}
	return (0);
	(void)av;
}
