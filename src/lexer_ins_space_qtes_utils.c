/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ins_space_qtes_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:27:42 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/10 16:29:59 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Initialize the i, j, dq and sq variables of insert_spaces_quotes() to 0.
*/
void	init_ints(int *i, int *j, int *dq, int *sq)
{
	*i = 0;
	*j = 0;
	*dq = 0;
	*sq = 0;
}
