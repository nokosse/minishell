/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:35:15 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/26 19:27:24 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Returns 1 if the quote is closed, 0 if not.
*/
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

/*
Doesn't copy the actual character ("), copy the rest until the next (").
and neither does it copy the last (").
*/
void	skip_dq_get_token(char **cmdl, char **token, int *i, int *k)
{
	(*i)++;
	while ((*cmdl)[*i] != '\"')
	{
		(*token)[*k] = (*cmdl)[*i];
		(*i)++;
		(*k)++;
	}
	(*i)++;
}

/*
Act like skip_dq_get_token but with single quotes, and this one actually
copies the actual character (') and the last one.
*/
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
char	*get_token(char *cmdl, int *j, bool *quote)
{
	int			i;	
	int			k;
	char		*token;

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
		{
			*quote = true;
			skip_dq_get_token(&cmdl, &token, &i, &k);
		}
		else if (cmdl[i] == '\'' && (is_quote_closed(cmdl, i, '\'')))
			skip_sq_get_token(&cmdl, &token, &i, &k);
		else
			token[k++] = cmdl[i++];
	}
	*j = i;
	return (token);
}

/*
This function will free every 'word' in the t_lex structure.
As well as every node of the linked list.
And finally, it will free the last node.
*/
void	free_lex(t_mini *shell)
{
	t_lex	*tmp;
	t_lex	*tmp2;
	int		i;

	i = 0;
	tmp = shell->lex;
	tmp2 = tmp;
	if (shell->nb_tokens == 0)
		return ;
	while (i < shell->nb_tokens)
	{
		tmp = tmp->next;
		free(tmp2->word);
		free(tmp2);
		tmp2 = tmp;
		i++;
	}
	if (tmp)
		free(tmp);
}
