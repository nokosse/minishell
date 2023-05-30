/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:59:05 by kvisouth          #+#    #+#             */
/*   Updated: 2023/05/30 13:03:19 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO :	afficher un historique
//			gerer les '' et les ""
//			gerer les redirections < > << >>
//			gerer les pipes |
//			gerer les variables d'environnement
//			gerer $?
//			gerer les signaux CTRL-C CTRL-D CTRL-\
//			gerer les builtins :
//				- echo (avec option -n)
//				- cd uniquement avec chemin relatif ou absolu
//				- pwd (pas d'option)
//				- export (pas d'option)
//				- unset (pas d'option)
//				- env (pas d'option & pas d'argument)
//				- exit (pas d'option)


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
