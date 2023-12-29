/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 10:42:43 by kevso             #+#    #+#             */
/*   Updated: 2023/12/29 17:31:08 by kvisouth         ###   ########.fr       */
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
void	free_all(t_mini *shell)
{
	if (shell->end == false)
	{
		shell->end = true;
		if (shell->lex_error == false)
			free_cmd(shell);
		free(shell->cmdline);
		if (shell->lex_error == false)
			free(shell->parsed_cmdline);
		free_lex(shell);
	}
}
