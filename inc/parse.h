/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:29:05 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/29 16:08:21 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include "structure.h"

/* LEXER PART */
int		lexer(t_mini *shell);
int		init_lex(t_mini *shell);
int		assign_word(t_mini *shell);
int		assign_token(t_mini *shell);
void	free_lex(t_mini *shell);
int		count_tokens(char *cmdl);
char	*get_token(char *cmdl, int *j);

/* PARSER PART */
void	parser(t_mini *shell);
void	parse_error(t_mini *shell);
void	free_cmd(t_mini *shell);

/* EXPANDER PART */

#endif