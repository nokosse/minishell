/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:42:22 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/18 18:35:55 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	assign_token(t_lex **lex)
{
	t_lex	*tmp;

	tmp = *lex;
	while (tmp)
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
	}
}

void	init_lex(t_lex **lex, char *str)
{
	int		i;
	int		nb_tokens;
	t_lex	*tmp;

	i = 0;
	nb_tokens = count_tokens(str);
	*lex = ft_calloc(1, sizeof(t_lex));
	if (!*lex)
		return ;
	tmp = *lex;
	while (i < nb_tokens - 1)
	{
		tmp->word = NULL;
		tmp->token = 0;
		tmp->next = ft_calloc(1, sizeof(t_lex));
		if (!tmp->next)
			return ;
		tmp = tmp->next;
		i++;
	}
}

/*
This function will assign a word to every nodes of the t_lex list.
Every words of every nodes will be the result of get_token().
*/
void	assign_word(t_lex **lex, char *str)
{
	t_lex	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = *lex;
	while (tmp)
	{
		tmp->word = get_token(str, &i);
		tmp->i = j;
		tmp = tmp->next;
		j++;
	}
}

void	lexer(t_mini *shell)
{
	t_lex		*lex;

	init_lex(&lex, shell->cmdline);
	assign_word(&lex, shell->cmdline);
	assign_token(&lex);

	//print lex
	t_lex	*tmp;
	tmp = lex;
	while (tmp)
	{
		printf("token = %s i = %d ", tmp->word, tmp->i);
		if (tmp->token == WORD)
			printf("token = WORD\n");
		else if (tmp->token == PIPE)
			printf("token = PIPE\n");
		else if (tmp->token == LEFT1)
			printf("token = LEFT1\n");
		else if (tmp->token == LEFT2)
			printf("token = LEFT2\n");
		else if (tmp->token == RIGHT1)
			printf("token = RIGHT1\n");
		else if (tmp->token == RIGHT2)
			printf("token = RIGHT2\n");
		tmp = tmp->next;
	}
}
