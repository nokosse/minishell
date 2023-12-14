/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_readline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 10:40:38 by kevso             #+#    #+#             */
/*   Updated: 2023/12/14 10:51:54 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
We will completely free the env.
Then free the cmdline.
And finally clear the history of readline.
*/
void	handle_readline_error(char **env, char *cmdline)
{
	free_arrplus(env);
	free(cmdline);
	rl_clear_history();
}
