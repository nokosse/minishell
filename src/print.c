/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:09:05 by operez            #+#    #+#             */
/*   Updated: 2023/06/13 16:45:26 by operez           ###   ########.fr       */
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
	k = 0;
	//ft_printf("Address cmd = %p\n", cmd);
	while (cmd)
	{
		if (cmd->bool_file)
		{
			print = cmd->dir;
			while (print)
			{
				print = print->next;
				k++;
			}
			ft_printf("Nbr de redirection = %d\n", k);
			if (cmd->dir->left)
			{
				if (cmd->dir->type == 2)
					ft_printf("Command %d contains '<<' with %s\n as file\n", j, cmd->dir->content);
				if (cmd->dir->type == 1)
					ft_printf("Command %d contains '<' with %s\n as file\n", j, cmd->dir->content);
			}
			if (cmd->dir->right)
			{
				if (cmd->dir->type == 2)
					ft_printf("Command %d contains '>>' with %s as file\n", j, cmd->dir->content);
				if (cmd->dir->type == 1)
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
