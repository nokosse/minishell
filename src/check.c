/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:14:03 by operez            #+#    #+#             */
/*   Updated: 2023/06/02 15:11:38 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
void	parse(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < 'a' && str[i] > 'z') && (str[i] < 'A' && str[i] > 'Z'))
			ft_printf("parse error near")
	}
}

int	check_tokens(t_cmd *cmd)
{
	int		i;
	char	**array;

	i = 0;
	array = cmd->tokens;
	while (array[i])
		i++;
	if (i == 0)
		parse
}
*/
void	check_pipes(char *str)
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
