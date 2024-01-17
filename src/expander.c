/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:51:28 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/17 14:46:15 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_env(t_mini *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}

/*
Returns the number of $ found in str
*/
int	count_dollars(char *str)
{
	int	i;
	int	nb_dollar;

	i = 0;
	nb_dollar = 0;
	while (str[i])
	{
		if (str[i] == '$')
			nb_dollar++;
		i++;
	}
	return (nb_dollar);
}

/*
Returns the lenght of the variable name.
Useful if we do $USER$PWD, will return 4 for USER and 3 for PWD.
*/
int	get_var_len(char *str, int i)
{
	int	len;

	len = 0;
	i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	return (len);
}

/*
Search and returns the content in **env of *var.
var = "USER", will search for USER=... in **env
And will return 'kvisouth' if USER=kvisouth
*/
char	*get_var_content(char **env, char *var)
{
	int	i;
	int j;
	char	*var_content;

	i = 0;
	var_content = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
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

char	*replace_var(t_mini *shell, char **word, int i, int len)
{
	char	*var;
	char	*var_content;
	char	*new;

	var = ft_substr(*word, i + 1, len);
	var_content = get_var_content(shell->env, var);
	new = ft_calloc(ft_strlen(*word) + ft_strlen(var_content) + 1, sizeof(char));
	if (!var || !var_content || !new)
		return (NULL);
	ft_strlcpy(new, *word, i + 1);
	ft_strlcat(new, var_content, ft_strlen(*word) + ft_strlen(var_content) + 1);
	ft_strlcat(new, *word + i + len + 1, ft_strlen(*word) + ft_strlen(var_content) + 1);
	free(*word);
	free(var);
	free(var_content);
	return (new);
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
	lex->nb_expansions = count_dollars(lex->word);
	while (word[i])
	{
		if (word[i] == '$')
		{
			len = get_var_len(word, i);
			word = replace_var(shell, &word, i, len);
			if (!word)
				return (0);
			i += len;
		}
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
