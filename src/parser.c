/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:21:56 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/19 11:49:11 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function will initialize the t_cmd linked list.
The number of nodes is the number of commands. Simple as that.
*/
int	init_cmd(t_mini *shell)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	shell->cmd = malloc(sizeof(t_cmd));
	if (!shell->cmd)
		return (0);
	tmp = shell->cmd;
	while (i < shell->nb_commands)
	{
		tmp->str = NULL;
		tmp->cmd = NULL;
		tmp->redir = NULL;
		tmp->nb_redir = 0;
		tmp->next = malloc(sizeof(t_cmd));
		if (!tmp->next)
			return (0);
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (1);
}

/*
This function will create the command. (It's a big one)
It will call multiple functions to fill every nodes of the t_cmd linked list.
*/
int	create_cmd(t_mini *shell)
{
	if (!get_cmdlines_in_nodes(shell))
		return (0);
	if (!get_cmd_in_nodes(shell))
		return (0);
	count_redir(shell);
	if (!get_redir_in_nodes(shell))
		return (0);
	return (1);
}

/*
The parser will create a linked list : 't_cmd' with 'create_cmd()'.
Most of the elements of this list will be pointers on the lexer tokens.
And 'parse_error()' will handle wrong inputs and prints "parse error".
*/
int	parser(t_mini *shell)
{
	shell->parse_error = false;
	count_pipes_and_commands(shell);
	if (!init_cmd(shell))
		return (0);
	if (!create_cmd(shell))
		return (0);
	print_cmd(shell);
	if (!parse_error(shell))
		return (0);
	return (1);
}
