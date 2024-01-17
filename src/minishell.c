/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:03:13 by kevso             #+#    #+#             */
/*   Updated: 2024/01/17 16:42:44 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This is where hell begins, the core of minishell.
lexer, parser, and executor will be called here.
The lexer can only fail malloc errors.
The parser can use exit codes if the syntax is wrong.
The executor can use exit codes if the command is wrong.
*/
void	start_minishell(t_mini *shell)
{
	shell->end = false;
	if (!lexer(shell))
	{
		shell->lex_error = true;
		free_all(shell);
		return ;
	}
	// print_lex(shell);
	if (!expander(shell))
	{
		free_all(shell);
		return ;
	}
	if (!parser(shell))
	{
		shell->parse_error = true;
		free_all(shell);
		return ;
	}
	// if (!executor(shell))
	// {
	// 	free_all(shell);
	// 	return ;
	// }
	print_cmd(shell);
}

/*
This is the loop where we will be able to type commands in our minishell.
start_minishell() will be the core of minishell, where the lexer, paser and
executor will be called.

With signal(SIGINT, handle_signal) we handle the ctrl + c signal which just
display a new prompt line.
With signal(SIGQUIT, SIG_IGN) we handle the ctrl + \ signal which just
does nothing thanks to SIG_IGN. (IGN for IGNORE)
*/
void	minishell_loop(t_mini *shell)
{
	char	*cmdline;

	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		cmdline = readline("minishell$> ");
		if (!cmdline)
		{
			free_arrplus(shell->env);
			free(cmdline);
			rl_clear_history();
			break ;
		}
		add_history(cmdline);
		shell->cmdline = cmdline;
		start_minishell(shell);
		free_all(shell);
	}
}

// TODO LEAK : quote followed by pipe : ' | ls 
// TODO LEAK : on : echo"e e e""er" 2 spaces in 1st arg
// TODO LEAK : pipe in quotes : "ls | ls"
// TODO : expand : WHEN to expand ? -> WHAT to expand ?
// TODO : improve 'end' to free only after check if not NULL
// TODO : parsing_error
// TODO : expander
// TODO ENV : SHLVL, OLDPWD, PWD updates

// PROBLEM : when $? followed by existing $VAR, $VAR doens't expand
// same problem instead of $? its a NULL var. (not existing)
// ex: $?$PWD -> 0$PWD instead of 0/home/kevso/42/minishell
// PROBLEM : lexer ins space insert spaces even in quotes (shouldnt)
// NOTE : ctrl + d with env -i -> has a % at the end of the prompt