/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:09:05 by operez            #+#    #+#             */
/*   Updated: 2023/06/02 15:09:08 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd)
	{
		if (cmd->bool_file)
		{
			if (cmd->dir->left)
			{
				if (cmd->dir->r_double)
					ft_printf("Command %d contains '<<' with %s\n as file\n", j, cmd->dir->content);
				else
					ft_printf("Command %d contains '<' with %s\n as file\n", j, cmd->dir->content);
			}
			if (cmd->dir->right)
			{
				if (cmd->dir->r_double)
					ft_printf("Command %d contains '>>' with %s as file\n", j, cmd->dir->content);
				else
					ft_printf("Command %d contains '>' with %s as file\n", j, cmd->dir->content);
			}
		}
		while (cmd->tokens[i])
		{
			if (i == 0)
			{
				ft_printf("Command = %s ", cmd->tokens[i++]);
				continue ;
			}
			ft_printf("Parameter = %s ", cmd->tokens[i++]);
		}
		cmd = cmd->next;
		j++;
		ft_printf("\n");
		i = 0;
	}
	ft_printf("\n");
}
