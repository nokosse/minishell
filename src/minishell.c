/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:03:13 by kevso             #+#    #+#             */
/*   Updated: 2024/01/19 18:11:45 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This is where hell begins, the core of minishell.
lexer, parser, expander and executor will be called here.
LEXER : Will just split the command line as space as delimiter.
PARSER : Will check if the command is valid, and fill the structure.
EXPANDER : Will tranform $USER into kvisouth. And so on.
EXECUTOR : Will execute the command.
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
	// print_cmd(shell);
	// if (!executor(shell))
	// {
	// 	free_all(shell);
	// 	return ;
	// }
	free_all(shell);
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
		cmdline = readline("minishell> ");
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

// TODO : improve 'end' to free only after check if not NULL
// TODO : parsing_error
// TODO ENV : SHLVL, OLDPWD, PWD updates

// TODO : improve parse_error with quote parsing + do redir parsing

// BIG PROBLEMS: (TO FIX!!)
// parsing :
// - echo "pipe|pipe" pipe inside quote does parsing error should NOT.
// because of the dquote trimmed, pipe inside dq are counted as real pipes.
// add in assign token to ignore pipe inside quotes // FIXED PIPEERR1
// - make parsing error parse raw cmdline because of dqoute trimmed
// exec : none

// MINOR PROBLEMS: (osef un peu)
// -"$USER"WDD -> expand void intread of kvisouthWDD
// Make sens because : "$USER"WDD is tokenized as $USERWDD which doesn't exist
// exec : none