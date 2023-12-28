/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:51:12 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/28 16:14:29 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function will handle the input errors.
*/
void	parse_error(t_mini *shell)
{
	printf("parse error\n");
	free_all(shell);
}
