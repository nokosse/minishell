/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 10:42:43 by kevso             #+#    #+#             */
/*   Updated: 2024/01/09 14:20:02 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Only free every elements of 'arr'.
*/
void	free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

/*
Free every elements of 'arr' and then free 'arr'.
*/
void	free_arrplus(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
Called to free everything. On malloc errors or exit or parsing errors..
Even execution errors etc..
*/
void	free_all(t_mini *shell)
{
	if (shell->end == false)
	{
		shell->end = true;
		if (shell->lex_error == false)
			free_cmd(shell);
		free(shell->cmdline);
		free_lex(shell);
	}
}

/*
This function will just free every nodes of the 'redir' linked list.
+ the last node.
*/
void	free_redir(t_cmd *cmd_t, int nb_redir)
{
	t_lex	*tmp;
	t_lex	*tmp2;
	int		i;

	i = 0;
	tmp = cmd_t->redir;
	tmp2 = tmp;
	while (i < nb_redir)
	{
		tmp = tmp->next;
		free(tmp2);
		tmp2 = tmp;
		i++;
	}
	free(tmp);
}

/*
This function frees in each nodes of t_cmd :
- 'str' (char *) : the raw command line.
- 'cmd' (char **) : the command and its arguments.
- 'redir' (t_lex *) : the redirections linked list. (with free_redir())
It does not free the 'char *word' in the t_lex linked list because it is a
'word' is a pointer to a token in the lexer which will be freed in free_lex()
after the parser.
*/
void	free_cmd(t_mini *shell)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;
	int		i;

	i = 0;
	tmp = shell->cmd;
	tmp2 = tmp;
	while (i < shell->nb_commands)
	{
		tmp = tmp->next;
		free(tmp2->str);
		free(tmp2->cmd);
		free_redir(tmp2, tmp2->nb_redir);
		free(tmp2);
		tmp2 = tmp;
		i++;
	}
	free(tmp);
}
