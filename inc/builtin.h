/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:31:52 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/21 13:23:13 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "structure.h"

/* CD */
int		builtin_cd(char **cmd, t_mini *shell);
int		update_env_pwd(char **env, char *cwd, char *old);
char	*trim_last_elem(char *cwd);
int		cd_count_args(char **cmd);
int		cd_handle_absolute(char *path);
int		cd_handle_relative(char *path, char *cwd);

/* ECHO */
int		builtin_echo(char **cmd);

/* ENV */
void	builtin_env(char **env);

/* EXIT */

/* EXPORT */

/* PWD */
void	builtin_pwd(void);

/* UNSET */

#endif