/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:02:46 by operez            #+#    #+#             */
/*   Updated: 2023/06/15 16:55:10 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*word_to_array(char *str, int i, int j, t_cmd **cmd)
{
	int		k;
	char	*tokens;

	if (str)
	{
		k = 0;
		if ((str[i] == '\'' || str[i] == '\"') && str[i] == str[i + j])
		{
			j--;
			i++;
		}
		tokens = malloc (sizeof(char) * (j + 1));
		if (!tokens)
			end(cmd);
		while (str[i] && k < j)
			tokens[k++] = str[i++];
		tokens[k] = '\0';
	}
	return (tokens);
}

t_dir	*ft_dirnew(t_cmd **cmd)
{
	t_dir	*tmp;

	tmp = malloc(sizeof(t_dir));
	if (!tmp)
		end(cmd);
	tmp->content= NULL;
	tmp->type= 0;
	tmp->left= 0;
	tmp->right= 0;
	tmp->next= NULL;
	return (tmp);
}

t_cmd	*ft_commandnew()
{
	t_cmd	*tmp;

	tmp = malloc (sizeof(t_cmd));
	if (!tmp)
		end(NULL);
	tmp->tokens_count = 0;
	tmp->bool_file = 0;
	tmp->dir = NULL;
	tmp->quote = 0;
	tmp->next = NULL;
	return (tmp);
}
