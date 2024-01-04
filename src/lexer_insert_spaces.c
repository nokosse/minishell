/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_insert_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:12:35 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/04 17:13:15 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Skip from the actual quote to the next one.
Increment i.
*/
void	skip_quotes_count_len(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
	if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\"')
			(*i)++;
	}
}

/*
Used to count the number of characters in the new command line to malloc it.
*/
int	count_len(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		skip_quotes_count_len(str, &i);
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if ((i > 0) && (str[i - 1] != ' ' && str[i - 1] != '<'
				&& str[i - 1] != '>' && str[i - 1] != '|'))
				nb++;
			if (str[i + 1] != ' ' && str[i + 1] != '<'
				&& str[i + 1] != '>' && str[i + 1] != '|')
				nb++;
		}
		i++;
	}
	return (nb + ft_strlen(str));
}

/*
Just skip from the actual quote to the next one.
Increment i and j.
*/
void	skip_quotes_insert_spaces(char *str, char *new, int *i, int *j)
{
	if (str[*i] == '\'')
	{
		new[*j] = str[*i];
		(*i)++;
		(*j)++;
		while (str[*i] && str[*i] != '\'')
		{
			new[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
	}
	if (str[*i] == '\"')
	{
		new[*j] = str[*i];
		(*i)++;
		(*j)++;
		while (str[*i] && str[*i] != '\"')
		{
			new[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
	}
}

/*
This function will insert spaces where it's needed.
It will insert in two cases :
1. if the char BEFORE the current is NOT a SPACE, LEFT1, RIGHT1 or PIPE
2. if the CURRENT char is NOT a SPACE, LEFT1, RIGHT1 or PIPE 
*/
void	handle_spaces(int *i, int *j, char **new, char *cmd)
{
	if ((*i > 0) && (cmd[*i - 1] != ' ' && cmd[*i - 1] != '<'
		&& cmd[*i - 1] != '>' && cmd[*i - 1] != '|'))
	{
		(*new)[*j] = ' ';
		(*j)++;
	}
	(*new)[*j] = cmd[*i];
	(*j)++;
	(*i)++;
	if (cmd[*i] != ' ' && cmd[*i] != '<' && cmd[*i] != '>'
		&& cmd[*i] != '|')
	{
		(*new)[*j] = ' ';
		(*j)++;
	}
}

/*
This function will insert spaces between the tokens.
To make 'ls>out' become 'ls > out' for example.
*/
int	insert_spaces(t_mini *shell)
{
	char	*new;
	char	*cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = shell->cmdline;
	new = ft_calloc(count_len(cmd) + 1, sizeof(char));
	if (!new)
		return (0);
	while (cmd[i])
	{
		skip_quotes_insert_spaces(cmd, new, &i, &j);
		if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|')
		{
			handle_spaces(&i, &j, &new, cmd);
		}
		else
			new[j++] = cmd[i++];
	}
	free(cmd);
	shell->cmdline = new;
	return (1);
}
