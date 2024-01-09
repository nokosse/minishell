/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:33:26 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/09 14:19:57 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
This function will use 'cmdline' and will fill 'str' in t_cmd.
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
		tmp->str = get_cmd(shell->cmdline, &j);
		if (!tmp->str)
			return (0);
		tmp = tmp->next;
		i++;
		j++;
	}
	return (1);
}
