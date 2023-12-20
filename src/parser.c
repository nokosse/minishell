/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:21:56 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/20 18:53:48 by kvisouth         ###   ########.fr       */
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
		return ;
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
	// Handle malloc error
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
		// Handle malloc error
		tmp = tmp->next;
		i++;
		j++;
	}
}
/*
This function will use 'str' and will fill 'cmd' in t_cmd.
cmd being an array of strings, cmd[0] will always be the command. (ls, wc..)
cmd[1-n] will be the argument(s) of the command. It is NULL if no arguments.
*/
void	get_cmd_in_nodes(t_mini *shell)
{

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
	tmp = shell->cmd;
	while (i < shell->nb_commands)
	{
		tmp->str = NULL;
		tmp->cmd = NULL;
		tmp->path = NULL;
		tmp->redir = NULL;
		tmp->next = malloc(sizeof(t_cmd));
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
}

/*
The parser will read the lexer linked list and will first : check the syntax.
Then it will logically separate the commands, arguments and tokens to create
a command. It will store the informations in the t_cmd structure.

From t_lex that looks like this :
word = "ls" and 	token = WORD	*next*
word = "-la" and 	token = WORD	*next*
word = "|" and 		token = PIPE	*next*
word = "wc" and 	token = WORD	*next*
word = "-l" and 	token = WORD	*next*
word = ">" and 		token = RIGHT1	*next*
word = "out" and	token = WORD	*next*
word = NULL and 	token = 0		*end*

Will give a t_cmd that looks like this :
path = "/bin/ls" and cmd = "ls -la" and	redir = NULL 		*next*
path = "/bin/wc" and cmd = "wc -l" and 	redir = "> out" 	*next*
path = NULL and 	 cmd = NULL and 	redir = NULL 		*end*
*/
void	parser(t_mini *shell)
{
	count_pipes_and_commands(shell);
	init_cmd(shell);
	create_cmd(shell);
}
