/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:21:56 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/03 14:45:40 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function will simply count the number of pipes in the t_lex linked list.
*/
void	count_pipes_and_commands(t_mini *shell)
{
	int		i;
	t_lex	*tmp;

	i = 0;
	shell->nb_pipes = 0;
	shell->nb_commands = 0;
	tmp = shell->lex;
	while (i < shell->nb_tokens)
	{
		if (tmp->token == PIPE)
			shell->nb_pipes++;
		tmp = tmp->next;
		i++;
	}
	shell->nb_commands = shell->nb_pipes + 1;
}

/*
This function will recreate the command line. (shell->parsed_cmdline)
At the moment, the command line is what the user typed.
It can have junk spaces, tabs, etc.. But now that the lexer has done its job,
we can just concatene all the 'words' in the t_lex linked list.
*/
int	get_clean_cmdline(t_mini *shell)
{
	t_lex	*tmp;
	int		len;
	int		i;

	len = ft_strlen(shell->cmdline);
	shell->parsed_cmdline = ft_calloc(len + 1, sizeof(char));
	if (!shell->parsed_cmdline)
		return (0);
	tmp = shell->lex;
	i = 0;
	while (i < shell->nb_tokens)
	{
		ft_strcat(shell->parsed_cmdline, tmp->word);
		if (shell->nb_tokens - i > 1)
			ft_strcat(shell->parsed_cmdline, " ");
		tmp = tmp->next;
		i++;
	}
	return (1);
}

/*
Returns all characters found before a PIPE if there is 1 or +.
Otherwise, if there is no PIPE, just returns cmdl.
Again, we take care to ignore the pipe if it is between simple/double quotes.
*/
char	*get_cmd(char *cmdl, int *j)
{
	int		i;
	int		k;
	char	*cmd;

	i = *j;
	k = 0;
	cmd = ft_calloc(ft_strlen(cmdl) + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	while (cmdl[i] && cmdl[i] == ' ')
		i++;
	while (cmdl[i] && cmdl[i] != '|')
	{
		if (cmdl[i] == '\'' || cmdl[i] == '\"')
		{
			cmd[k++] = cmdl[i++];
			while (cmdl[i] && cmdl[i] != '\'' && cmdl[i] != '\"')
				cmd[k++] = cmdl[i++];
		}
		if (cmdl[i] && cmdl[i] != '|')
			cmd[k++] = cmdl[i++];
	}
	*j = i;
	return (cmd);
}

/*
This function will use 'parsed_cmdline' and will fill 'str' in t_cmd.
It will put everything before a PIPE in the 'str' var in each nodes of t_cmd.
The last command is not before a pipe, so it will be the last node.
You can notice that this function is very similar to assign_word() in lexer.c
*/
int	get_cmdlines_in_nodes(t_mini *shell)
{
	t_cmd		*tmp;
	int			i;
	static int	j;

	i = 0;
	j = 0;
	tmp = shell->cmd;
	while (i < shell->nb_commands)
	{
		tmp->str = get_cmd(shell->parsed_cmdline, &j);
		if (!tmp->str)
			return (0);
		tmp = tmp->next;
		i++;
		j++;
	}
	return (1);
}

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

/*
This function will create the command. (It's a big one)
It will call multiple functions to fill every nodes of the t_cmd linked list.
*/
int	create_cmd(t_mini *shell)
{
	if (!get_clean_cmdline(shell))
		return (0);
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
	if (!parse_error(shell))
		return (0);
	return (1);
}
