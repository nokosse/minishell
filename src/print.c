/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:09:05 by operez            #+#    #+#             */
/*   Updated: 2023/06/16 19:10:35 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print(t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;
	t_dir	*print;

	i = 0;
	j = 0;
	//ft_printf("Address cmd = %p\n", cmd);
	while (cmd)
	{
		while (cmd->tokens[i])
		{
			if (i == 0)
			{
				ft_printf("Command %d = %s ", j, cmd->tokens[i++]);
				continue ;
			}
			ft_printf("Parameter = %s ", cmd->tokens[i++]);
		}
		ft_printf("\n");
		if (cmd->bool_file)
		{
			k = 0;
			print = cmd->dir;
			while (print)
			{
				print = print->next;
				k++;
			}
			ft_printf("Command %d contains %d redirection:\n", j, k);
			while (cmd->dir)
			{
				if (cmd->dir->left)
				{
					if (cmd->dir->type == 2)
						ft_printf("<< with \"%s\" as file\n", cmd->dir->content);
					if (cmd->dir->type == 1)
						ft_printf("< with \"%s\" as file\n", cmd->dir->content);
				}
				if (cmd->dir->right)
				{
					if (cmd->dir->type == 2)
						ft_printf(">> with \"%s\" as file\n", cmd->dir->content);
					if (cmd->dir->type == 1)
						ft_printf("> with \"%s\" as file\n", cmd->dir->content);
				}
				cmd->dir = cmd->dir->next;
			}
		}
		cmd = cmd->next;
		j++;
		ft_printf("\n");
		i = 0;
	}
	// ft_printf("\n");
}
