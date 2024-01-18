/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:29:36 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/18 16:54:35 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "structure.h"

// All the functions related to the execution part of minishell

int executor(t_mini *shell);
int exec_simple(t_mini *shell);
int exec_multiple(t_mini *shell);

#endif