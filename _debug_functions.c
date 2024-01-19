/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ___________________________________________        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:22:14 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/18 14:34:12 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function is for debug purposes only.
It prints every info on every nodes of t_cmd.
*/
void	print_cmd(t_mini *shell)
{
	t_cmd	*tmp;
	t_lex	*tmp2;
	int		i;
	int		j;

	i = 0;
	tmp = shell->cmd;
	if (shell->nb_tokens == 0)
		return ;
	if (shell->nb_tokens == 1 && shell->lex->token == PIPE)
		return ;
	while (i < shell->nb_commands)
	{
		write(1, "\n", 1);
		printf("[RAW COMMAND] str = %s\n", tmp->str);
		j = 0;
		while (tmp->cmd[j])
		{
			printf("[CMD ARRAY %d] cmd = '%s'\n", j, tmp->cmd[j]);
			j++;
		}
		printf("\n");
		printf("nb_redir = %d\n", tmp->nb_redir);
		tmp2 = tmp->redir;
		j = 0;
		while (j < tmp->nb_redir)
		{
			printf("[FILE/DELIM] redir[%d] = %s\n", j, tmp2->word);
			if (tmp2->token == RIGHT1)
				printf("[REDIR TYPE] token[%d] = >\n", j);
			else if (tmp2->token == RIGHT2)
				printf("[REDIR TYPE] token[%d] = >>\n", j);
			else if (tmp2->token == LEFT1)
				printf("[REDIR TYPE] token[%d] = <\n", j);
			else if (tmp2->token == LEFT2)
				printf("[REDIR TYPE] token[%d] = <<\n", j);
			tmp2 = tmp2->next;
			j++;
		}
		tmp = tmp->next;
		i++;
	}
	write(1, "\n", 1);
}

void	print_lex(t_mini *shell)
{
	t_lex	*tmp;
	int		i;

	i = 0;
	tmp = shell->lex;
	while (i < shell->nb_tokens)
	{
		printf("\nword[%d] = \'%s\'\n", i, tmp->word);
		tmp = tmp->next;
		i++;
	}
}
