/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 10:42:43 by kevso             #+#    #+#             */
/*   Updated: 2023/12/28 15:30:46 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Only free every elements of 'arr'.
*/
void	free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

/*
Free every elements of 'arr' and then free 'arr'.
*/
void	free_arrplus(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
Called to free everything. On malloc errors or exit or parsing errors..
Even execution errors etc..
*/
void	end(t_mini *shell)
{
	if (shell->end == false)
	{
		shell->end = true;
		free_cmd(shell);
		free(shell->cmdline);
		free(shell->parsed_cmdline);
		free_lex(shell);
	}
}
