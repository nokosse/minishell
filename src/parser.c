/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:21:56 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/29 18:01:22 by kvisouth         ###   ########.fr       */
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
void	get_clean_cmdline(t_mini *shell)
{
	t_lex	*tmp;
	int		len;
	int		i;

	len = ft_strlen(shell->cmdline);
	shell->parsed_cmdline = ft_calloc(len + 1, sizeof(char));
	if (!shell->parsed_cmdline)
		free_all(shell);
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
void	get_cmdlines_in_nodes(t_mini *shell)
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
			free_all(shell);
		tmp = tmp->next;
		i++;
		j++;
	}
}

/*
This function will allocate the right number or arrays 'cmd' needs.
*/
void	allocate_cmd_arrays(t_mini *shell)
{
	t_cmd	*cmd_t;
	t_lex	*lex_t;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd_t = shell->cmd;
	lex_t = shell->lex;
	while (i < shell->nb_tokens)
	{
		if (lex_t->token == WORD)
			j++;
		if (lex_t->token == PIPE || i == shell->nb_tokens - 1)
		{
			cmd_t->cmd = malloc(sizeof(char *) * (j + 1));
			if (!cmd_t->cmd)
				free_all(shell);
			cmd_t = cmd_t->next;
			j = 0;
		}
		lex_t = lex_t->next;
		i++;
	}
}

/*
This function will fill the 'cmd' array in every nodes of t_cmd.
cmd[i] will be a pointer to a 'WORD' token in the lexer.
*/
void	get_cmd_in_nodes(t_mini *shell)
{
	t_cmd	*cmd_t;
	t_lex	*lex_t;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd_t = shell->cmd;
	lex_t = shell->lex;
	allocate_cmd_arrays(shell);
	while (i < shell->nb_tokens)
	{
		if (lex_t->token == WORD)
			cmd_t->cmd[j++] = lex_t->word;
		if (lex_t->token == PIPE || i == shell->nb_tokens - 1)
		{
			cmd_t->cmd[j] = NULL;
			cmd_t = cmd_t->next;
			j = 0;
		}
		lex_t = lex_t->next;
		i++;
	}
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
void	init_redir(t_cmd *tmp, t_mini *shell)
{
	int		i;
	t_lex	*tmp2;

	i = 0;
	tmp->redir = malloc(sizeof(t_lex));
	if (!tmp->redir)
		free_all(shell);
	tmp2 = tmp->redir;
	while (i < tmp->nb_redir)
	{
		tmp2->i = 0;
		tmp2->token = 0;
		tmp2->next = malloc(sizeof(t_lex));
		if (!tmp2->next)
			free_all(shell);
		tmp2 = tmp2->next;
		i++;
	}
	tmp2->next = NULL;
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
void	get_redir_in_nodes(t_mini *shell)
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
			init_redir(tmp_cmd, shell);
			get_tokens_and_words(tmp_cmd, tmp_lex, &lex_pos);
		}
		tmp_cmd = tmp_cmd->next;
		i++;
	}
}

/*
This function will create the command. (It's a big one)
It will call multiple functions to fill every nodes of the t_cmd linked list.
*/
void	create_cmd(t_mini *shell)
{
	get_clean_cmdline(shell);
	get_cmdlines_in_nodes(shell);
	get_cmd_in_nodes(shell);
	count_redir(shell);
	get_redir_in_nodes(shell);
	print_cmd(shell); //delete later
}

/*
This function will initialize the t_cmd linked list.
The number of nodes is the number of commands. Simple as that.
*/
void	init_cmd(t_mini *shell)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	shell->cmd = malloc(sizeof(t_cmd));
	if (!shell->cmd)
		free_all(shell);
	tmp = shell->cmd;
	while (i < shell->nb_commands)
	{
		tmp->str = NULL;
		tmp->cmd = NULL;
		tmp->redir = NULL;
		tmp->nb_redir = 0;
		tmp->next = malloc(sizeof(t_cmd));
		if (!tmp->next)
			free_all(shell);
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
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
	init_cmd(shell);
	create_cmd(shell);
	parse_error(shell);
	return (1);
}
