/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:42:22 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/29 18:34:52 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function will initialize the t_lex structure.
It first malloc the first node of the linked list with sizeof(t_lex).
Then loops 'nb_tokens' times, init the values of the structure.
Then malloc the next node with sizeof(t_lex).
Finally, it sets the next node to NULL. (the one after the last one)
*/
int	init_lex(t_mini *shell)
{
	t_lex	*tmp;
	int		i;

	i = 0;
	shell->lex = malloc(sizeof(t_lex));
	if (!shell->lex)
		return (0);
	tmp = shell->lex;
	while (i < shell->nb_tokens)
	{
		tmp->i = i;
		tmp->word = NULL;
		tmp->token = 0;
		tmp->next = malloc(sizeof(t_lex));
		if (!tmp->next)
			return (0);
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (1);
}

/*
This function will fill the 'word' variable in the t_lex structure.
It will loop 'nb_tokens' times, and call get_token() to get the 'word'.
'i' is the index of the token.
'j' is a static because we want to keep track of the index of the command line
for get_token(). It is the index of a character in the cmdline.
*/
int	assign_word(t_mini *shell)
{
	t_lex		*tmp;
	int			i;
	static int	j;

	i = 0;
	j = 0;
	tmp = shell->lex;
	while (i < shell->nb_tokens)
	{
		tmp->word = get_token(shell->cmdline, &j);
		if (!tmp->word)
			return (0);
		tmp = tmp->next;
		i++;
		j++;
	}
	return (1);
}

/*
This function will assign the token identifier to the a word.
It's simple, if the word is a '|' we give it the token PIPE.
If it's a '<' we give it the token LEFT1 and so on..
Otherwise, it's a WORD.
*/
int	assign_token(t_mini *shell)
{
	t_lex	*tmp;
	int		i;

	i = 0;
	tmp = shell->lex;
	while (i < shell->nb_tokens)
	{
		if (!ft_strcmp(tmp->word, "|"))
			tmp->token = PIPE;
		else if (!ft_strcmp(tmp->word, "<"))
			tmp->token = LEFT1;
		else if (!ft_strcmp(tmp->word, "<<"))
			tmp->token = LEFT2;
		else if (!ft_strcmp(tmp->word, ">"))
			tmp->token = RIGHT1;
		else if (!ft_strcmp(tmp->word, ">>"))
			tmp->token = RIGHT2;
		else
			tmp->token = WORD;
		tmp = tmp->next;
		i++;
	}
	return (1);
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

/*
The Lexer is a lexical analyser, meaning it will not check for syntax errors.
It will just analyse what is a letter, what is a pipe, what is a redirection.
After analysing, it will store these informations in a structure.
*/
int	lexer(t_mini *shell)
{
	shell->lex_error = false;
	shell->nb_tokens = count_tokens(shell->cmdline);
	if (shell->nb_tokens == 0)
		return (0);
	if (!init_lex(shell))
		return (0);
	if (!assign_word(shell))
		return (0);
	if (!assign_token(shell))
		return (0);
	return (1);
}
