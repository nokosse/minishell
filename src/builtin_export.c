/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:21:21 by kvisouth          #+#    #+#             */
/*   Updated: 2023/06/01 10:21:22 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
}
char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

int	check_trgh_env(char **tokens, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(tokens[1], env[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**builtin_export(char **tokens, char **env)
{
	int		len;
	int		i;
	char	**array;

	if (check_trgh_env(tokens, env))
	{
		len = 0;
		i = 0;
		while (env[len])
			len++;
		array = malloc(sizeof(char *) * (len + 3));
		if (!array)
			return (0);			//suivi de malloc
		while (env[i])
		{
			array[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
			if (!array[i])
				free_array(array);
			array[i] = ft_strcpy(array[i], env[i]);
			i++;
		}
		array[i] = malloc(sizeof(char) * (ft_strlen(tokens[0]) + 1));
		if (!array[i])
			free_array(array);
		array[i] = ft_strcpy(array[i], tokens[1]);
		array[++i] = '\0';
		free(env);
		env = array;
	}
	return (env);
}
