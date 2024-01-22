/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:31:52 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/22 18:01:42 by kvisouth         ###   ########.fr       */
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
void	builtin_exit(t_mini *shell, char **cmd);

/* EXPORT */
int		builtin_export(char **cmd, t_mini *shell);
int		exp_count_args(char **cmd);
int		env_count(char **env);
int		var_already_exist(char *var, t_mini *shell);
int		exp_check_args(char **cmd);

/* PWD */
void	builtin_pwd(void);

/* UNSET */

#endif