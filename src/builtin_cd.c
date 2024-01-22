/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:48:04 by kvisouth          #+#    #+#             */
/*   Updated: 2024/01/22 12:14:31 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function will return 0 either if there is only 1 argument (only cd)
or if there is more than 2 arguments (cd .. ..)
Else, it will return 1.
*/
int	cd_handle_invalid_args(char **cmd)
{
	if (cd_count_args(cmd) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_sig = 1;
		return (0);
	}
	else if (cd_count_args(cmd) == 0)
	{
		ft_putstr_fd("cd: not enough arguments\n", 2);
		g_sig = 1;
		return (0);
	}
	return (1);
}

/*
This function will handle the case where we type 'cd ..'
cwd with getcwd will get the current directory as a string.
we will then trim the last element of the path. (see trim_last_elem)
Then we will change directory to the new trimmed path.
*/
int	cd_handle_prev_dir(char *cwd)
{
	char	*str;

	str = NULL;
	getcwd(cwd, 1024);
	str = trim_last_elem(cwd);
	if (!str)
		return (0);
	if (chdir(str) != 0)
	{
		g_sig = 1;
		free(str);
		return (0);
	}
	g_sig = 0;
	free(str);
	return (1);
}

/*
This function will handle the case where we type 'cd /'
We will change directory to the root directory by using chdir("/")
*/
int	cd_handle_root_dir(void)
{
	if (chdir("/") != 0)
	{
		g_sig = 1;
		return (0);
	}
	g_sig = 0;
	return (1);
}

/*
This function will handle cd when we type a string as an argument.
If the string starts with '/', we will use cd_handle_absolute
Else, we will use cd_handle_relative
*/
int	cd_handle_str(char *path, char *cwd)
{
	if (path[0] == '/')
	{
		if (!cd_handle_absolute(path))
			return (0);
	}
	else
	{
		if (!cd_handle_relative(path, cwd))
			return (0);
	}
	return (1);
}

/*
Basically, how does 'cd' works :
- We only accept 1 argument to it.
- We handle th case where we type 'cd ..'
- We handle the case where we type 'cd /'
- We handle the case where we type 'cd <string>' (cd /Users or cd minishell)
We will use the environment variable PWD to get the current directory.
and then trim or add or replace what the user typed with cd.
then update the environment variable PWD and OLDPWD.
OLDPWD is saved before any changes in the function, and PWD is saved after.
*/
int	builtin_cd(char **cmd, t_mini *shell)
{
	char	cwd[1024];
	char	oldpwd[1024];

	getcwd(oldpwd, 1024);
	if (!cd_handle_invalid_args(cmd))
		return (0);
	if (!ft_strcmp(cmd[1], ".."))
	{
		if (!cd_handle_prev_dir(cwd))
			return (0);
	}
	else if (!ft_strcmp(cmd[1], "/"))
	{
		if (!cd_handle_root_dir())
			return (0);
	}
	else
	{
		if (!cd_handle_str(cmd[1], cwd))
			return (0);
	}
	getcwd(cwd, 1024);
	update_env_pwd(shell->env, cwd, oldpwd);
	return (1);
}
