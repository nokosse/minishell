/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_cmd_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:36:00 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/03 15:36:09 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
A long IF statement that I moved in this function to make the code shorter
for norm issues.
It checks if the previous token is NOT a Redirection and the current token
is a WORD.
*/
int	check_prev_token(t_lex *lex_t, int prev_token)
{
	if (prev_token != RIGHT1 && prev_token != RIGHT2
		&& prev_token != LEFT1 && prev_token != LEFT2
		&& lex_t->token == WORD)
		return (1);
	return (0);
}

/*
Same, just init variables for norm issues.
*/
void	init_i_j_prev(int *i, int *j, int *prev_token)
{
	*i = 0;
	*j = 0;
	*prev_token = -1;
}

/*
Same, just init variables for norm issues.
*/
void	init_cmd_lex(t_mini *shell, t_cmd **cmd_t, t_lex **lex_t)
{
	*cmd_t = shell->cmd;
	*lex_t = shell->lex;
}

/*
This function will allocate the right number or arrays 'cmd' needs.
*/
int	allocate_cmd_arrays(t_mini *shell)
{
	t_cmd	*cmd_t;
	t_lex	*lex_t;
	int		i;
	int		j;
	int		prev_token;

	init_i_j_prev(&i, &j, &prev_token);
	init_cmd_lex(shell, &cmd_t, &lex_t);
	while (i < shell->nb_tokens)
	{
		if (check_prev_token(lex_t, prev_token))
			j++;
		if (lex_t->token == PIPE || i == shell->nb_tokens - 1)
		{
			cmd_t->cmd = malloc(sizeof(char *) * (j + 1));
			if (!cmd_t->cmd)
				return (0);
			cmd_t = cmd_t->next;
			j = 0;
		}
		prev_token = lex_t->token;
		lex_t = lex_t->next;
		i++;
	}
	return (1);
}

/*
This function will fill the 'cmd' array in every nodes of t_cmd.
cmd[i] will be a pointer to a 'WORD' token in the lexer.
*/
int	get_cmd_in_nodes(t_mini *shell)
{
	t_cmd	*cmd_t;
	t_lex	*lex_t;
	int		i;
	int		j;
	int		prev_token;

	init_i_j_prev(&i, &j, &prev_token);
	init_cmd_lex(shell, &cmd_t, &lex_t);
	if (!allocate_cmd_arrays(shell))
		return (0);
	while (i < shell->nb_tokens)
	{
		if (check_prev_token(lex_t, prev_token))
			cmd_t->cmd[j++] = lex_t->word;
		if (lex_t->token == PIPE || i == shell->nb_tokens - 1)
		{
			cmd_t->cmd[j] = NULL;
			cmd_t = cmd_t->next;
			j = 0;
		}
		prev_token = lex_t->token;
		lex_t = lex_t->next;
		i++;
	}
	return (1);
}
