/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:02:46 by operez            #+#    #+#             */
/*   Updated: 2023/05/30 16:26:14 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '|')
	{
		ft_printf("parse error near '|'");		//ecrire sur sortie erreur
		return (0);
	}
	return (1);
}

t_cmd	*ft_commandnew()
{
	t_cmd	*tmp;

	tmp = malloc (sizeof(t_cmd));
	if (!tmp)
		end();
	tmp->tokens_count = 0;
	tmp->bool_file = 0;
	tmp->bool_single= 0;
	tmp->next = NULL;
	return (tmp);
}
