/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:32:39 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/18 16:48:11 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int executor(t_mini *shell)
{
    if (shell->nb_commands == 1)
    {
        if (!exec_simple(shell))
            return (0);
    }
    else
    {
        if (!exec_multiple(shell))
            return (0);
    }
    return (1);
}