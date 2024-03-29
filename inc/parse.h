/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:29:05 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/26 13:23:13 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include "structure.h"

/* LEXER: Main functions */
int		lexer(t_mini *shell);
int		init_lex(t_mini *shell);
int		assign_word(t_mini *shell);
int		assign_token(t_mini *shell);
int		count_tokens(char *cmdl);
char	*get_token(char *cmdl, int *j, bool *quote);

/* LEXER: Insert spaces */
int		count_len(char *str);
int		insert_spaces(t_mini *shell);
void	init_ints(int *i, int *j, int *dq, int *sq);
int		insert_spaces_quotes(t_mini *shell);
int		is_inside_dq(int i, char *str);
int		is_inside_sq(int i, char *str);
int		dq_is_closed(char *cmd, int i);
int		sq_is_closed(char *cmd, int i);
int		is_evn_dq(int i, int dq, t_mini *shell);
int		is_evn_sq(int i, int sq, t_mini *shell);

/* LEXER: Utils */
int		is_quote_closed(char *str, int i, char quote);
void	skip_double_quotes_2strings(char **cmd, char **new, int *i, int *k);
void	skip_simple_quotes_2strings(char **cmd, char **new, int *i, int *k);
int		avoid_early_errors(t_mini *shell);

/* LEXER: Error handling */
int		lexer_error(t_mini *shell);
void	free_lex(t_mini *shell);

/* PARSER : FILL CMD STRUCTURE PART */
int		parser(t_mini *shell);
void	free_cmd(t_mini *shell);
void	count_pipes_and_commands(t_mini *shell);
void	count_redir(t_mini *shell);
int		get_cmd_in_nodes(t_mini *shell);
int		get_redir_in_nodes(t_mini *shell);
int		get_cmdlines_in_nodes(t_mini *shell);

/* PARSER : HANDLE SYNTAX ERRORS PART */
int		is_quote(char *str, char c);
int		is_junk_char(char c);
void	skip_any_quote(char *str, int *i, char c);
int		handle_sq(char *str, int *i, int *sq);
int		handle_dq(char *str, int *i, int *dq);
int		parse_error(t_mini *shell);
int		handle_unclosed_quote_err(char *str);

/* EXPANDER PART */
int		expander(t_mini *shell);
int		get_var_len(char *str, int i);
int		count_dollars(char *str);
int		is_to_expand(char *word, int i);

#endif