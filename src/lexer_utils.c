/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:35:15 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/18 10:14:17 by kvisouth         ###   ########.fr       */
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

int	is_quote_closed(char *str, int i, char quote)
{
	int	j;

	j = i + 1;
	while (str[j] && str[j] != quote)
		j++;
	if (str[j] == quote)
		return (1);
	return (0);
}

void	skip_dq_get_token(char **cmdl, char **token, int *i, int *k)
{
	(*token)[*k] = (*cmdl)[*i];
	(*i)++;
	(*k)++;
	while ((*cmdl)[*i] != '\"')
	{
		(*token)[*k] = (*cmdl)[*i];
		(*i)++;
		(*k)++;
	}
	(*token)[*k] = (*cmdl)[*i];
	(*i)++;
	(*k)++;
}

void	skip_sq_get_token(char **cmdl, char **token, int *i, int *k)
{
	(*token)[*k] = (*cmdl)[*i];
	(*i)++;
	(*k)++;
	while ((*cmdl)[*i] != '\'')
	{
		(*token)[*k] = (*cmdl)[*i];
		(*i)++;
		(*k)++;
	}
	(*token)[*k] = (*cmdl)[*i];
	(*i)++;
	(*k)++;
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
		if (cmdl[i] == '\"' && (is_quote_closed(cmdl, i, '\"')))
			skip_dq_get_token(&cmdl, &token, &i, &k);
		else if (cmdl[i] == '\'' && (is_quote_closed(cmdl, i, '\'')))
			skip_sq_get_token(&cmdl, &token, &i, &k);
		else
			token[k++] = cmdl[i++];
	}
	*j = i;
	return (token);
}
