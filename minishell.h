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
	char	*content;				//nom du ficher cree
	int		r_double;			// si = 1 ; double chevron (<< ou >>)
	int		right;				//si = 1 ; chevron droit >
	int		left;
	struct s_dir	*next;
}	t_dir;

// 2 commandes, 2 listes, 2 structures.
typedef struct s_cmd //structure de UNE commande (liste chainée)
{
	char		**tokens;			//tableau de commandes
	int			tokens_count;		//nombre de tokens par commande
	int			bool_file;		//indique si chevron present dans la commande
	int			quote;			//si quote = 1 => '  quote = 2 => " 
	struct s_dir	*dir;
	struct s_cmd	*next;
}	t_cmd;

void	lexer(char *str, char **envp);
char	*word_to_array(char *str, int i, int j, t_cmd **cmd);
int	move_through_quote(char *str, int i, char c);
int	handle_redirection(t_cmd **cmd, char *str, int *i, int print);
int	is_valid_dir(t_cmd **cmd, char *str, int *i);
void	set_bool_file(t_cmd **cmd);
int     check_string(char *str);
t_cmd	*ft_commandnew();
t_dir	*ft_dirnew(t_cmd **cmd);
t_cmd	*ft_cmdlast(t_cmd *cmd);
t_dir	*ft_dirlast(t_dir *dir);
void	end(t_cmd **cmd);
int     is_whitespace(char c);
int	is_valid_char(char c);
int     is_quote(char *str, int i, char c);
int	move_through_quote(char *str, int i, char c);
void	free_struct(t_cmd **cmd);
void	ft_print(t_cmd *cmd);					//delete at the end of project

// Execution part
void	executor(char **tokens, char **envp);

// Built-ins part
void	exec_builtins(char **cmd, char **envp);
int		check_builtins(char *cmd);
int 	builtin_echo(char **args);

#endif
