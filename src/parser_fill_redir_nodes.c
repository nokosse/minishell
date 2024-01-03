/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_redir_nodes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:37:28 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/03 15:37:49 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function will fill the 'nb_redir' variable in every nodes of t_cmd.
It will count the number of tokens that are NOT 'WORD' / 'PIPE' until
the next 'PIPE' or the end of the command line.
*/
void	count_redir(t_mini *shell)
{
	t_cmd	*cmd_t;
	t_lex	*lex_t;
	int		i;

	i = 0;
	cmd_t = shell->cmd;
	lex_t = shell->lex;
	while (i < shell->nb_tokens)
	{
		if (lex_t->token != WORD && lex_t->token != PIPE)
			cmd_t->nb_redir++;
		if (lex_t->token == PIPE)
			cmd_t = cmd_t->next;
		lex_t = lex_t->next;
		i++;
	}
}

/*
Will initialize the same amount of nodes as shell->cmd->nb_redir.
redir being the same structure as lex, it will initialise the same values
(i, word, token, next).
*/
int	init_redir(t_cmd *tmp)
{
	int		i;
	t_lex	*tmp2;

	i = 0;
	tmp->redir = malloc(sizeof(t_lex));
	if (!tmp->redir)
		return (0);
	tmp2 = tmp->redir;
	while (i < tmp->nb_redir)
	{
		tmp2->i = 0;
		tmp2->token = 0;
		tmp2->next = malloc(sizeof(t_lex));
		if (!tmp2->next)
			return (0);
		tmp2 = tmp2->next;
		i++;
	}
	tmp2->next = NULL;
	return (1);
}

/*
This function will fill the 'token' and 'word' var in every nodes of
the 'redir' linked list in the actual node of t_cmd.
*/
void	get_tokens_and_words(t_cmd *cmd_t, t_lex *lex, int *lex_pos)
{
	int		i;
	t_lex	*redir_t;

	i = 0;
	redir_t = cmd_t->redir;
	while (i < cmd_t->nb_redir)
	{
		while ((lex->i < *lex_pos) && lex->next)
			lex = lex->next;
		while (lex->token != RIGHT1 && lex->token != RIGHT2
			&& lex->token != LEFT1 && lex->token != LEFT2)
		{
			if (lex->next == NULL)
				break ;
			lex = lex->next;
			(*lex_pos)++;
		}
		redir_t->token = lex->token;
		redir_t->word = lex->next->word;
		redir_t = redir_t->next;
		lex = lex->next;
		(*lex_pos)++;
		i++;
	}
}

/*
This function will fill the 'redir' linked list in every nodes of t_cmd.
It will first fill the 'word' var with the filename or the delimitor.
Then it will fill the 'token' var with the type of redirection.
*/
int	get_redir_in_nodes(t_mini *shell)
{
	t_cmd	*tmp_cmd;
	t_lex	*tmp_lex;
	int		lex_pos;
	int		i;

	i = 0;
	lex_pos = 0;
	tmp_cmd = shell->cmd;
	tmp_lex = shell->lex;
	while (i < shell->nb_commands)
	{
		if (tmp_cmd->nb_redir > 0)
		{
			if (!init_redir(tmp_cmd))
				return (0);
			get_tokens_and_words(tmp_cmd, tmp_lex, &lex_pos);
		}
		tmp_cmd = tmp_cmd->next;
		i++;
	}
	return (1);
}
