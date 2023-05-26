#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		if (!strcmp(line, "exit"))
		{
			free (line);
			break ;
		}
		lexer(line, envp);
	}
	return (0);
}
