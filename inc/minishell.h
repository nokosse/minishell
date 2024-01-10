/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:42:53 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/10 14:28:12 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <string.h>
# include <stdio.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <stddef.h>
# include <termios.h>
# include <sys/stat.h>
# include "exec.h"
# include "parse.h"
# include "structure.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"

extern int	g_sig;

// Frees
void	free_all(t_mini *shell);
void	free_arr(char **arr);
void	free_arrplus(char **arr);

// Error handling
void	handle_readline_error(char **env, char *cmdline);

char	**ft_init_env(char **env_cpy, char **env_og);
void	minishell_loop(t_mini *shell);
void	handle_signal(int sig);

// DEBUG
void    print_lex(t_mini *shell);
void	print_cmd(t_mini *shell);

#endif