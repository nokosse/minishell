/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:29:05 by kvisouth          #+#    #+#             */
/*   Updated: 2023/12/18 18:37:26 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include "structure.h"

// Lexer part
void	lexer(t_mini *shell);
int		count_tokens(char *cmdl);
char	*get_token(char *cmdl, int *j);
void	assign_word(t_lex **lex, char *str);
void	init_lex(t_lex **lex, char *str);
void	assign_token(t_lex **lex);

#endif