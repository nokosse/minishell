/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:20:53 by kvisouth          #+#    #+#             */
/*   Updated: 2023/06/01 12:58:07 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_str(char *str)
{
	int	i;
	int	rtn;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == '/')
			break ;
		i--;
	}
	rtn = ft_strlen(str) - i;
	return (rtn);
}

char	*extract_string(char *cwd)
{
	int		len;
	int		i;
	char	*str;

	i = 0;
	len = ft_strlen(cwd) - size_str(cwd);
	str = malloc (sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = cwd[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*join_str(char *cwd, char *tokens)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_strlen(cwd) + ft_strlen(tokens) + 1;
	str = malloc (sizeof(char) * size + 1);
	if (!str)
		return (0);
	while (cwd[i])
	{
		str[i] = cwd[i];
		i++;
	}
	str[i++] = '/';
	while (tokens[j])
		str[i++] = tokens[j++];
	str[i] = '\0';
	return (str);
}

void	builtin_cd(char **tokens)
{
	char	cwd[1024];
	char	*str;

	if (!ft_strcmp(tokens[1], ".."))
	{
		getcwd(cwd, 1024);
		str = extract_string(cwd);
		chdir(str);
		free(str);
	}
	else if (tokens[1][0] == '/')
		chdir(tokens[1]);
	else
	{
		getcwd(cwd, 1024);
		str = join_str(cwd, tokens[1]);
		chdir(str);
		free(str);
	}
}
