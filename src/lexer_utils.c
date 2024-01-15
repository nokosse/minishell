/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:35:15 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/15 12:37:28 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Count the number of tokens in the command line.
We take care not to split the tokens if they are between simple/double quotes !
*/
int	count_tokens(char *cmdl)
{
	int	i;
	int	nb_tokens;

	i = 0;
	nb_tokens = 0;
	while (cmdl[i])
	{
		if (cmdl[i] == '\'' || cmdl[i] == '\"')
		{
			i++;
			while (cmdl[i] && cmdl[i] != '\'' && cmdl[i] != '\"')
				i++;
		}
		if (cmdl[i] && cmdl[i] != ' ')
		{
			nb_tokens++;
			while (cmdl[i] && cmdl[i] != ' ')
				i++;
		}
		if (cmdl[i] && cmdl[i] == ' ')
			i++;
	}
	return (nb_tokens);
}

/*
Skips i to the next quote if closed.
*/
void	skip_dq_get_token(int *i, char *cmd)
{
	int	flg;

	if (cmd[*i] == '\"')
	{
		flg = *i;
		while (cmd[*i] != '\"' && cmd[*i])
			flg++;
		if (cmd[*i] == '\"')
			*i = flg;
	}
}

void	skip_sq_get_token(int *i, char *cmd)
{
	int	flg;

	if (cmd[*i] == '\'')
	{
		flg = *i;
		while (cmd[*i] != '\'' && cmd[*i])
			flg++;
		if (cmd[*i] == '\'')
			*i = flg;
	}	
}

/*
Returns a token from the command line and a static index.
We take care to ignore the space if it is between simple/double quotes.
*/
char	*get_token(char *cmdl, int *j)
{
	int		i;
	int		k;
	char	*token;

	i = *j;
	k = 0;
	token = ft_calloc(ft_strlen(cmdl) + 1, sizeof(char));
	if (!token)
		return (NULL);
	while (cmdl[i] && cmdl[i] == ' ')
		i++;
	while (cmdl[i] && cmdl[i] != ' ')
	{
		skip_dq_get_token(&i, cmdl);
		skip_sq_get_token(&i, cmdl);
		token[k++] = cmdl[i++];
	}
	*j = i;
	return (token);
}
