/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:33:26 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/03 15:41:15 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
