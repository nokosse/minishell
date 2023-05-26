#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/inc/libft.h"
# include "./ft_printf/ft_printf.h"
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

void	lexer(char *str, char **envp);
t_list	*ft_lstnew_s(char *content);
void	executor(char **tokens, char **envp);

#endif
