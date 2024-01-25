/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:17:21 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/25 13:50:21 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function will update the env variable PWD and OLDPWD
For PWD, we will just use getcwd to get the current directory, the same way we
did when we initialized the shell without env.
For OLDPWD, we will use the 'old' parameter which is the result of
getcwd at the start of the builtin_cd function.
*/
int	update_env_pwd(char **env, char *cwd, char *old)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			str = ft_strjoin("PWD=", cwd);
			if (!str)
				return (0);
			free(env[i]);
			env[i] = str;
		}
		else if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			str = ft_strjoin("OLDPWD=", old);
			if (!str)
				return (0);
			free(env[i]);
			env[i] = str;
		}
		i++;
	}
	return (1);
}

/*
This function is called only when we type 'cd ..'
Which means, we want to go back to the previous directory.
So what will this function do : cwd as parameter is our current directory.
We will want to trim the last element of the path.
Example : /Users/kvisouth/Desktop/minishell
Returns : /Users/kvisouth/Desktop -> minishell has been trimmed.
*/
char	*trim_last_elem(char *cwd)
{
	int		len;
	int		i;
	char	*str;

	i = 0;
	len = ft_strlen(cwd);
	while (cwd[len] != '/')
		len--;
	if (len != 0)
		len--;
	str = ft_calloc(len + 2, sizeof(char));
	if (!str)
		return (NULL);
	while (i <= len)
	{
		str[i] = cwd[i];
		i++;
	}
	return (str);
}

/*
Count the number of arrays in cmd
*/
int	cd_count_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

/*
This function will handle the case where we type 'cd /'
We will just change chdir to '/'.
*/
int	cd_handle_absolute(char *path)
{
	if (chdir(path) != 0)
	{
		g_sig = 1;
		ft_putstr_fd("cd: no such file or directory", 2);
		return (0);
	}
	g_sig = 0;
	return (1);
}

/*
This function will handle the case where we type 'cd minishell' for example.
We will get the current directory with getcwd.
Then add a '/' to it.
Then add the 'path' after the '/' we just added.
Then we will chdir to that new string which would look like :
/Users/kvisouth/Desktop/minishell and was previously /Users/kvisouth/Desktop
*/
int	cd_handle_relative(char *path, char *cwd)
{
	char	*str;

	str = NULL;
	getcwd(cwd, 1024);
	str = ft_strjoin(cwd, "/");
	if (!str)
		return (0);
	cwd = ft_strjoin(str, path);
	if (!cwd)
		return (0);
	free(str);
	if (chdir(cwd) != 0)
	{
		g_sig = 1;
		free(cwd);
		ft_putstr_fd("cd: no such file or directory", 2);
		return (0);
	}
	g_sig = 0;
	free(cwd);
	return (1);
}
