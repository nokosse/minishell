/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:09:37 by kevso             #+#    #+#             */
/*   Updated: 2023/12/14 10:11:06 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
We will check if envp is empty.
*/
int	ft_check_empty(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	if (i == 0)
		return (1);
	return (0);
}

/*
We will get the current directory path with getcwd() in variable 'buffer'.
Then we will create a string with "PWD=" and the path (buffer).
We malloc len + 5 because len is only the path, and the 5 is for "PWD=" and '\0'
We will just concat "PWD=" and buffer to have for example "PWD=/users/kevso"
*/
char	*ft_get_pwd(void)
{
	char	*buffer;
	char	*tmp;
	int		len;

	buffer = NULL;
	tmp = NULL;
	len = 0;
	buffer = getcwd(buffer, 0);
	if (buffer == NULL)
		return (NULL);
	len = ft_strlen(buffer);
	tmp = (char *)malloc(sizeof(char) * (len + 5));
	if (tmp == NULL)
		return (NULL);
	ft_strcpy(tmp, "PWD=");
	ft_strcat(tmp, buffer);
	free(buffer);
	return (tmp);
}

/*
We will create a clean env with only PWD, SHLVL and _. (That's why we malloc 4)
- PWD is the current directory, nothing new
- SHLVL is the current level of the shell, SH for shell, lvl for level..
- _ (underscore) is just the name of the last command you typed.
*/
char	**create_env(char **env_cpy)
{
	env_cpy = (char **)malloc(sizeof(char *) * 4);
	if (env_cpy == NULL)
		return (NULL);
	env_cpy[0] = ft_get_pwd();
	env_cpy[1] = ft_strdup("SHLVL=1");
	env_cpy[2] = ft_strdup("_=usr/bin/env");
	env_cpy[3] = NULL;
	if (env_cpy[0] == NULL || env_cpy[1] == NULL || env_cpy[2] == NULL)
		return (NULL);
	return (env_cpy);
}

/*
We will just return a copy of env_og.
*/
char	**copy_env(char **env_og)
{
	int		i;
	int		max;
	char	**env_cpy;

	i = 0;
	max = 0;
	env_cpy = NULL;
	while (env_og[max])
		max++;
	env_cpy = (char **)malloc(sizeof(char *) * (max + 1));
	if (env_cpy == NULL)
		return (NULL);
	while (i < max)
	{
		env_cpy[i] = ft_strdup(env_og[i]);
		if (env_cpy[i] == NULL)
			return (NULL);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

/*
If minishell is launched with 'env -i ./minishell'
Then we will have to create a clean env with only PWD, SHLVL and _.
Else, we will just copy all the envp (env_og) to our own env (env_cpy)
Of course we handle malloc errors that can occur in copy_env().
*/

char	**ft_init_env(char **env_cpy, char **env_og)
{
	if (ft_check_empty(env_og))
	{
		env_cpy = create_env(env_cpy);
		return (env_cpy);
	}
	else
	{
		env_cpy = copy_env(env_og);
		if (env_cpy == NULL)
			return (NULL);
		return (env_cpy);
	}
	return (NULL);
}
