/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:42:51 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/21 17:00:26 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "minishell.h"

/*
Wow, what's 'enum' ?
We use enums to avoid using magic numbers and macros.
It's a way to give a name to a set of values.
It just makes things easier to read and understand.
In this case for example, in t_lex, word = "ls" and token = WORD.
Instead of doing something like : word = "ls" and token = 1
I could write in comment 1 = WORD but it would be less understandable
in the rest of the code.
In the rest of the code we will be able to use this like :
if (t_lex->token == WORD)
	printf("It's a word !\n");
*/
typedef enum s_token
{
	WORD,
	PIPE,
	LEFT1,
	LEFT2,
	RIGHT1,
	RIGHT2,
}	t_token;

/*
t_lex will be the structure that will store all the informations about a token
'i' is just an index.
'word' is the token. It can be 'ls', '>', '|', ' "hello" ' ...
'token' is the TYPE of the token. 'ls' will be a WORD, '>' will be RIGHT1, etc..

This function will also be used as 'redir' in t_cmd for a complete different use.
'word' will be the filename or the delimitor of a redirection/heredoc
'token' will be the type of redirection (RIGHT1, LEFT2, etc..)
*/
typedef struct s_lex
{
	int				i;
	char			*word;
	t_token			token;
	struct s_lex	*next;
}	t_lex;

/*
t_cmd will be the structure that will store all the informations about a command
This will be the result of the parser.
'str' is the raw command line. "ls -la > output.txt"
'cmd' will be the command and its arguments. ['ls', '-la', NULL]
'path' will be the path of the command. "/bin/ls"
'redir' will be the redirections and it's filename or delimitor.
*/
typedef struct s_cmd
{
	char			*str;
	char			**cmd;
	t_lex			*redir;
	struct s_cmd	*next;
}	t_cmd;

/*
t_mini will be the main structure of minishell.
It has no next pointers, but t_cmd does.
It has no next pointers because this structure stores all the main informations
about minishell we could need everytime, like the env for example.
*/
typedef struct s_mini
{
	t_cmd	*cmd;
	t_lex	*lex;
	int		nb_pipes;
	int		nb_commands;
	int		nb_tokens;
	char	*path;
	char	**env;
	char	*parsed_cmdline;
	char	*cmdline;
}	t_mini;

#endif