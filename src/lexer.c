/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:42:22 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/16 16:33:47 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function will count the number of tokens in 'cmdl' to malloc the
right size for the array of tokens in the lexer.

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
This function will return a token from the command line.

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
		if (cmdl[i] == '\'' || cmdl[i] == '\"')
		{
			token[k++] = cmdl[i++];
			while (cmdl[i] && cmdl[i] != '\'' && cmdl[i] != '\"')
				token[k++] = cmdl[i++];
		}
		token[k++] = cmdl[i++];
	}
	token[k] = '\0';
	*j = i;
	return (token);
}

/*
The lexer (Lexical Analyzer)
The lexer is dumb and will simply 'split' the input into tokens.
It will read the input from the prompt once the user presed enter
and will split the informations into tokens in a 2D array of strings.
If we give the input : " ls -la | wc -l > outfile "
The lexer will return : [ "ls", "-la", "|", "wc", "-l", ">", "outfile" ]
in a char **.
*/
void	lexer(t_mini *shell)
{
	int			nb_tokens;
	int			i;
	static int	j = 0;

	nb_tokens = count_tokens(shell->cmdline);
	shell->tokens = malloc(sizeof(char *) * (nb_tokens + 1));
	if (!shell->tokens)
		return ;
	shell->tokens[nb_tokens] = NULL;
	i = 0;
	j = 0;
	while (i < nb_tokens)
	{
		shell->tokens[i] = get_token(shell->cmdline, &j);
		i++;
	}
}
