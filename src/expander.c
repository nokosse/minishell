/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:51:28 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/18 12:22:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Search and returns the content in **env of *var.
var = "USER", will search for USER=... in **env
And will return 'kvisouth' if USER=kvisouth
*/
char	*get_var_content(char **env, char *var)
{
	int		i;
	int		j;
	char	*var_content;

	i = 0;
	var_content = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& env[i][ft_strlen(var)] == '=')
		{
			j = 0;
			while (env[i][j] != '=')
				j++;
			var_content = ft_substr(env[i], j + 1, ft_strlen(env[i]));
			if (!var_content)
				return (NULL);
			return (var_content);
		}
		i++;
	}
	return (NULL);
}

/*
This function expands one variable.
It takes 'word' which is the token of lexer that contains the var. to expand.
It returns a new string which is word with a variable at 'i' expanded.

First, strlcpy will copy the first part of word (the part before $VAR)
Then, the first strlcat will add the variable content to the new string.
And the last strlcat will add the remaining part of word to the new string.

con stands for content (norm issues)
*/
char	*replace_var(t_mini *shell, char **word, int i, int len)
{
	char	*var;
	char	*con;
	char	*new;

	var = ft_substr(*word, i + 1, len);
	if (len == 1 && (*word)[i + 1] == '?')
	{
		shell->expanded_sig = 1;
		con = ft_itoa(g_sig);
	}
	else
		con = get_var_content(shell->env, var);
	if (!con)
	{
		con = ft_strdup("");
		shell->expanded_void = 1;
	}
	new = ft_calloc(ft_strlen(*word) + ft_strlen(con) + 1, sizeof(char));
	if (!var || !new)
		return (NULL);
	ft_strlcpy(new, *word, i + 1);
	ft_strlcat(new, con, ft_strlen(*word) + ft_strlen(con) + 1);
	ft_strlcat(new, *word + i + len + 1, ft_strlen(*word) + ft_strlen(con) + 1);
	return (free(*word), free(var), free(con), new);
}

/*
Transforms every $... into the value of the variable.
$USER$USER = "kvisouthkvisouth"
$NONEXISTING = ""
*/
int	expand_var(t_mini *shell, t_lex *lex)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	word = lex->word;
	while (word[i])
	{
		shell->expanded_void = 0;
		shell->expanded_sig = 0;
		if (is_to_expand(word, i))
		{
			len = get_var_len(word, i);
			word = replace_var(shell, &word, i, len);
			if (!word)
				return (0);
			if (!shell->expanded_void && !shell->expanded_sig)
				i += len;
		}
		if (!shell->expanded_void)
			i++;
	}
	lex->word = word;
	return (1);
}

/*
The expander will iterate through lex words.
It will expand every $... it finds execpt it the word is between simple quotes.
Non existing variables will be replaced by an empty string.
Special case is the $? variable.
*/
int	expander(t_mini *shell)
{
	t_lex	*lex_t;
	int		i;

	lex_t = shell->lex;
	lex_t->nb_expansions = count_dollars(lex_t->word);
	i = 0;
	while (i < shell->nb_tokens)
	{
		if (!is_quote(lex_t->word, '\'') && count_dollars(lex_t->word))
		{
			if (!expand_var(shell, lex_t))
				return (0);
		}
		lex_t = lex_t->next;
		i++;
	}
	return (1);
}
