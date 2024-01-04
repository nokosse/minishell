/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:51:28 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/04 16:26:13 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
The expander takes variables, identified by $, and replaces them with their
value from the environment variables. Such that $USER becomes kvisouth
and $? is replaced with the exit code.
*/
int	expander(t_mini *shell)
{
	(void)shell;
	return (1);
}
