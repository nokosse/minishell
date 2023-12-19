/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:29:05 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/19 17:18:06 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include "structure.h"

/* LEXER PART */
void	lexer(t_mini *shell);
void	init_lex(t_mini *shell);
void	assign_word(t_mini *shell);
void	assign_token(t_mini *shell);
void	free_lex(t_mini *shell);
int		count_tokens(char *cmdl);
char	*get_token(char *cmdl, int *j);

/* PARSER PART */

/* EXPANDER PART */

#endif