/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:29:05 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/02 18:18:06 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include "structure.h"

/* LEXER PART */
int		lexer(t_mini *shell);
int		insert_spaces(t_mini *shell);
int		init_lex(t_mini *shell);
int		assign_word(t_mini *shell);
int		assign_token(t_mini *shell);
int		count_tokens(char *cmdl);
char	*get_token(char *cmdl, int *j);
int		lexer_error(t_mini *shell);
void	free_lex(t_mini *shell);

/* PARSER : FILL CMD STRUCTURE PART */
int		parser(t_mini *shell);
void	free_cmd(t_mini *shell);

/* PARSER : HANDLE SYNTAX ERRORS PART */
int		parse_error(t_mini *shell);
int		handle_unclosed_quote_err(t_mini *shell);

/* EXPANDER PART */

#endif