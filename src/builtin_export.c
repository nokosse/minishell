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
char	*ft_strcat(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		s1[i++] = s2[j++];
	s1[i] = '\0';
	return (s1);

}
void	builtin_export(char **tokens, char ***env)
{
	int		len;
	int		i;
	char	**array;
	char	**ev;

	len = 0;
	i = 0;
	ev = *env;
	while (ev[len])
		len++;
	array = malloc(sizeof(char *) * (len + 3));
	if (!array)
		return ;			//suivi de malloc
	while (ev[i])
	{
		array[i] = malloc(sizeof(char) * (ft_strlen(ev[i]) + 1));
		if (!array[i])
			free_array(array);
		array[i] = ft_strcpy(array[i], ev[i]);
		i++;
	}
	array[i] = malloc(sizeof(char) * (ft_strlen(tokens[0]) + 1));
	if (!array[i])
		free_array(array);
	array[i] = ft_strcpy(array[i], tokens[1]);
	free(ev);
	ev = array;
	*env = ev;
}
