/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:02:46 by operez            #+#    #+#             */
/*   Updated: 2023/06/13 17:08:37 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_char(char c)
{
	if (c == '\0')
		return (0);
	if ( c == '\\' || c == ':' || c == '*' || c == '?' || c == ';'
		|| c == '&' || c == '(' || c == ')'
		|| c == '$' || c == '!')
		return (0);
	return (1);
}

int	is_quote(char *str, int i, char c)
{
	if (c == '\'' || c == '\"')
	{
		while (str[++i])
		{
			if (str[i] == c)
			{
				if (str[i] == '\'')
					return (1);
				if (str[i] == '\"')
					return (2);
			}
		}
	}
	return (0);
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
	ft_dirnew(&tmp);
	return (tmp);
}
