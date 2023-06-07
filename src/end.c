/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:35:28 by operez            #+#    #+#             */
/*   Updated: 2023/05/30 11:36:24 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_struct(t_cmd **cmd)
{
	t_cmd	*tmp;
	int	i;

	i = 0;
	tmp = *cmd;
	if (tmp->tokens)
	{
		while (tmp->tokens[i])
			free(tmp->tokens[i++]);
		free (tmp->tokens);
	}
	if (tmp->dir)
	{
		if (tmp->dir->content)
			free(tmp->dir->content);
		free(tmp->dir);
	}
}

void	end(t_cmd **cmd)
{
	if (cmd)
		free_struct(cmd);
	exit(EXIT_SUCCESS);
}
