/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:21:29 by kvisouth          #+#    #+#             */
/*   Updated: 2023/06/01 10:21:31 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var_name(char *tokens, char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=' && tokens[i] == env[i])
		i++;
	if (env[i] == '=')
		return (1);
	return (0);
}

char	**builtin_unset(char **tokens, char **env)
{
	int		len;
	int		i;
	int		j;
	char	**array;

	if (check_trgh_env(tokens, env))
	{
		len = 0;
		i = 0;
		j = 0;
		while (env[len])
			len++;
		array = malloc (sizeof(char *) * len);
		if (!array)
			return (0);
		while (env[i + j])
		{
			if (is_var_name(tokens[1], env[i + j]))
				j++;
			if (i + j == len)
				break ;
			array[i] = malloc(sizeof(char) * (ft_strlen(env[i + j]) + 1));
			if (!array[i])
				free_array(array);
			array[i] = ft_strcpy(array[i], env[i + j]);
			i++;
		}
		array[i] = '\0';
		free(env);
		env = array;
	}
	return (env);
}
