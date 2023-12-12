/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:42:51 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/12 15:33:15 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "minishell.h"

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
}			t_cmd;

typedef struct s_mini
{
	t_cmd	*cmd;
	int		nb_cmd;
}			t_mini;

#endif