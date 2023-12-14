/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:33:24 by kevso             #+#    #+#             */
/*   Updated: 2023/12/14 15:30:41 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This is the function that will handle the signal SIGINT (ctrl + c).

rl_on_new_line() will move the cursor to the next line.
rl_replace_line() will replace the current line with it's arguments (empty).
rl_redisplay() will refresh the prompt to apply the two previous functions.
*/
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
