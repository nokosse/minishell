/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:21:56 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/19 17:48:19 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
The parser will read the lexer linked list and will first : check the syntax.
Then it will logically separate the commands, arguments and tokens to create
a command. It will store the informations in the t_cmd structure.

From t_lex that looks like this :
word = "ls" and 	token = WORD	*next*
word = "-la" and 	token = WORD	*next*
word = "|" and 		token = PIPE	*next*
word = "wc" and 	token = WORD	*next*
word = "-l" and 	token = WORD	*next*
word = ">" and 		token = RIGHT1	*next*
word = "out" and	token = WORD	*next*
word = NULL and 	token = 0		*end*

Will give a t_cmd that looks like this :
path = "/bin/ls" and cmd = "ls -la" and	redir = NULL 		*next*
path = "/bin/wc" and cmd = "wc -l" and 	redir = "> out" 	*next*
path = NULL and 	 cmd = NULL and 	redir = NULL 		*end*
*/
void	parser(t_mini *shell)
{
	printf("parser\n");
	(void)shell;
}
