/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:02:46 by operez            #+#    #+#             */
/*   Updated: 2023/06/02 15:21:19 by operez           ###   ########.fr       */
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
	t_cmd	*tmp;

	tmp = *cmd;
	tmp->dir = malloc(sizeof(t_dir));
	if (!tmp->dir)
		end(cmd);
	tmp->dir->content= NULL;
	tmp->dir->r_double= 0;
	tmp->dir->left= 0;
	tmp->dir->right= 0;
	tmp->dir->next= NULL;
	return (tmp->dir);
}

t_cmd	*ft_commandnew()
{
	t_cmd	*tmp;

	tmp = malloc (sizeof(t_cmd));
	if (!tmp)
		end(NULL);
	tmp->tokens_count = 0;
	tmp->bool_file = 0;
	tmp->quote = 0;
	tmp->next = NULL;
	ft_dirnew(&tmp);
	return (tmp);
}
