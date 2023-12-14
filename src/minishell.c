/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:03:13 by kevso             #+#    #+#             */
/*   Updated: 2023/12/14 14:32:23 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This is where hell begins, the core of minishell.
lexer, parser, and executor will be called here.
*/
void	start_minishell(t_mini *shell)
{
	printf("cmdline = %s\n", shell->cmdline);
}

/*
This is the loop where we will be able to type commands in our minishell.
start_minishell() will be the core of minishell, where the lexer, paser and
executor will be called.
*/
void	minishell_loop(t_mini *shell)
{
	char	*cmdline;

	while (1)
	{
		cmdline = readline("minishell$> ");
		if (!cmdline)
		{
			handle_readline_error(shell->env, cmdline);
			break ;
		}
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		add_history(cmdline);
		shell->cmdline = cmdline;
		start_minishell(shell);
	}
}
