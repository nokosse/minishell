#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/inc/get_next_line.h"
# include "libft/inc/libft.h"
# include "libft/inc/ft_printf.h"
# include "./libft/inc/libft.h"
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
# include <termios.h>

typedef struct s_dir
{
	char	*content;
	int		r_double;
	int		left;
	int		right;
	struct s_dir	*next;
}	t_dir;

// 2 commandes, 2 listes, 2 structures.
typedef struct s_cmd //structure de UNE commande (liste chainée)
{
	char		**tokens; //tableau de tableau des commandes et arguments
	int			tokens_count;
	int			bool_file;
	struct s_dir	*dir;
	struct s_cmd	*next;
}	t_cmd;

void	lexer(char *str, char **envp);
char	*word_to_array(char *str, int i, int j);
void	handle_redirection(t_cmd **cmd, char *str, int *i);
void	ignore_param(t_cmd *cmd, char *str, int *i);
int     check_string(char *str);
t_cmd	*ft_commandnew();
t_dir	*ft_dirnew(t_cmd **cmd);
void	end();
int     is_whitespace(char c);
void	ft_print(t_cmd *cmd);					//delete at the end of project

// Execution part
void	executor(char **tokens, char **envp);

// Built-ins part
void	exec_builtins(char **cmd, char **envp);
int		check_builtins(char *cmd);
int 	builtin_echo(char **args);

#endif
