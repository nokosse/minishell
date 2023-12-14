/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:42:51 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/14 10:59:37 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "minishell.h"

/*
t_cmd will be the structure that will store all the informations about a command
It has a next pointer because minishell handle multiple commands via pipes (|)
Example : ls -la | wc -l
t_cmd will store all the informations about 'ls -la' like the path, the command
the arguments, etc...
We will need to use pointer next to have all the informations about 'wc -l' etc.
*/
typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	struct s_cmd	*next;
}	t_cmd;

/*
t_mini will be the main structure of minishell.
It has no next pointers, but t_cmd does.
It has no next pointers because this structure stores all the main informations
about minishell we could need everytime, like the env for example.
*/
typedef struct s_mini
{
	t_cmd	*cmd;
	int		nb_cmd;
}	t_mini;

#endif