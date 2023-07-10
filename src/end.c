/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:35:28 by operez            #+#    #+#             */
/*   Updated: 2023/07/10 11:34:22 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Double free detectee quand on execute plusieurs commande avec un pipe
void	free_struct(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*copy;
	t_dir	*save;
	int	i;

	tmp = *cmd;
	while (tmp)
	{
		i = 0;
		if (tmp->tokens)
		{
			while (tmp->tokens[i])
				free(tmp->tokens[i++]);
			free (tmp->tokens);
		}
		if (tmp->ptr_line)
			free(tmp->ptr_line);
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
		copy = tmp;
		tmp = tmp->next;
		free(copy);
	}
}

void	end(t_cmd **cmd)
{
	if (cmd)
		free_struct(cmd);
	exit(EXIT_SUCCESS);
}
