/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:03:13 by kevso             #+#    #+#             */
/*   Updated: 2024/01/04 17:45:16 by kvisouth         ###   ########.fr       */
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
	print_cmd(shell); //tu peux l'enlever ou le remettre quand tu veux
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

// TODO : leaks on : even number of quotes
// TODO : in lexer_insert_spaces, improve quote skipping to avoid leaks
// TODO : improve unclosed quote error handling
// TODO : improve 'end' to free only after check if not NULL
// TODO : parsing_error
