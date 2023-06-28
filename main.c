/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:59:05 by kvisouth          #+#    #+#             */
/*   Updated: 2023/06/15 16:40:31 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	g_signal;

#include "minishell.h"

// TODO :	afficher un historique
//			gerer les '' et les ""
//			gerer les redirections < > << >>
//			gerer les pipes |
//			gerer les variables d'environnement
//			gerer $?
//			gerer les signaux CTRL-C CTRL-D CTRL-\ //
//			gerer les builtins :
//				- echo (avec option -n)
//				- cd uniquement avec chemin relatif ou absolu
//				- pwd (pas d'option)
//				- export (pas d'option)
//				- unset (pas d'option)
//				- env (pas d'option & pas d'argument)
//				- exit (pas d'option)


void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 130;
	}
	if (signal == SIGQUIT)
	{
		printf("\33[2K\r");
		rl_on_new_line();
		rl_redisplay();
	}
}

char	**set_env(char ***env, char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	copy = *env;
	while (envp[i])
		i++;
	copy = malloc (sizeof(char *) * i + 1);
	if (!copy)
		exit(EXIT_FAILURE);
	i = 0;
	while (envp[i])
	{
		copy[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		if (!copy[i])
			free_array(copy);
		copy[i] = ft_strcpy(copy[i], envp[i]);
		i++;
	}
	return (copy);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	static char		**env;
	struct sigaction	sa;

	env = NULL;
	env = set_env(&env, envp);
	if (argc == 1)
	{
		(void) argv;
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = handle_signal;
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		while (1)
		{
			line = readline("minishell> ");
			if (!line)
			{
				free (line);
				rl_clear_history();
				break ;
			}
			if (!ft_strlen(line))
			{
				free(line);
				continue ;
			}
			add_history(line);
			if (!strcmp(line, "exit"))
			{
				free(line);
				rl_clear_history();
				break ;
			}
			ft_printf("env2 = %p\n", env);
			lexer(line, &env);
			free(line);
		}
	}
	return (0);
}
