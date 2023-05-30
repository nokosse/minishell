/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:19:51 by operez            #+#    #+#             */
/*   Updated: 2023/05/30 12:25:56 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*word_to_array(char *str, int i, int j)
{
	int		k;
	char	*tokens;

	k = 0;
	tokens = malloc (sizeof(char) * (j + 1));
	if (!tokens)
		return (0);					//follow return
	while (i < j)
		tokens[k++] = str[i++];
	tokens[k] = '\0';
	return (tokens);
}

void	get_token(char *str, char **tokens)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] == ' ')
			i++;
		while (str[i + j] && str[i + j] != ' ')
			j++;
		if (str[i] != '\0')
			tokens[k] = word_to_array(str, i, j);
		while (str[i] && str[i] != ' ')
			i++;
	}
}

int	tokens_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && str[i] != ' ')
			i++;
	}
	return (count);
}

void	lexer(char *str, char **envp)
{
	char	**tokens;

	tokens = malloc (sizeof(char *) * (tokens_count(str) + 1));
	if (!tokens)
		return ;							//end
	get_token(str, tokens);
	executor(tokens, envp);
}

//creer liste chaine de contenant char** / bool variable: < ou > && << ou >> = Variable true si
//chevron gauche, false si droit et simple ou double chevron
