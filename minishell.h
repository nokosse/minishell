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

typedef struct s_cmd
{
	char		**tokens;
	int			tokens_count;
	int			bool_file;
	int			bool_single;
	struct s_cmd	*next;
}	t_cmd;

void	lexer(char *str, char **envp);
int     check_string(char *str);
t_cmd	*ft_commandnew();
void	executor(char **tokens, char **envp);
void	end();

#endif
