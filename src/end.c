/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:35:28 by operez            #+#    #+#             */
/*   Updated: 2023/06/13 17:25:19 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_struct(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_dir	*save;
	int	i;

	i = 0;
	tmp = *cmd;
	// penser a free ensemble liste chaine de commandes 
	if (tmp->tokens)
	{
		while (tmp->tokens[i])
			free(tmp->tokens[i++]);
		free (tmp->tokens);
	}
	if (tmp->dir)
	{
		while (tmp->dir)
		{
			save = tmp->dir;
			if (tmp->dir->content)
				free(tmp->dir->content);
			tmp->dir = tmp->dir->next;
			free(save);
		}
	}
	free(tmp);
}

void	end(t_cmd **cmd)
{
	if (cmd)
		free_struct(cmd);
	exit(EXIT_SUCCESS);
}
