/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:29:36 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/19 11:10:17 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "structure.h"

// All the functions related to the execution part of minishell

int		executor(t_mini *shell);
int		ft_same_str(char *str1, char *str2, size_t n);
char	*ft_strjoin_free1(char const *s1, char const *s2);

#endif