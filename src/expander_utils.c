/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:03:44 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/18 10:05:04 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Returns the number of $ found in str
So we know how many variables we need to expand or simply if we need to expand.
*/
int	count_dollars(char *str)
{
	int	i;
	int	nb_dollar;

	i = 0;
	nb_dollar = 0;
	while (str[i])
	{
		if (str[i] == '$')
			nb_dollar++;
		i++;
	}
	return (nb_dollar);
}

/*
Returns the lenght of the variable name.
Useful if we do $USER$PWD, will return 4 for USER and 3 for PWD.
*/
int	get_var_len(char *str, int i)
{
	int	len;

	len = 0;
	i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
	{
		len++;
		i++;
	}
	return (len);
}

/*
Returns 1 if the actual character (word[i]) is a $ and need to be expanded.
*/
int	is_to_expand(char *word, int i)
{
	if (word[i] == '$' && word[i + 1] && (ft_isalnum(word[i + 1])
			|| word[i + 1] == '_' || word[i + 1] == '?'))
	{
		return (1);
	}
	return (0);
}
