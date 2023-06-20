/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:02:46 by operez            #+#    #+#             */
/*   Updated: 2023/06/20 17:07:33 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
				var = malloc(sizeof(char) * i + 1);
				if (!var)
					end(&cmd);
				var = ft_strncpy(var, env[k], i);
				return (var);*/
#include "../minishell.h"

char	*ft_strncpy(char *s1, char *s2, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

int	is_env_var(t_cmd *cmd, char *str, int i)
{
	char	**env;
	int		j;
	int		k;
	int		save;

	k = 0;
	save = i;
	env = cmd->ptr_env;
	while (env[k])
	{
		i = save;
		j = 0;
		if (str[i] == env[k][j])
		{
			while (str[i] == env[k][j])
			{
				i++;
				j++;
			}
			if (env[k][j] == '=')
			{
				ft_printf("is env\n");
				return (1);
			}
		}
		k++;
	}
	ft_printf("is not env\n");
	return (0);
}

int	size_var(t_cmd *cmd, char *str, int i)
{
	int		j;
	int		k;
	int		l;
	char	**env;

	k = 0;
	j = 0;
	env = cmd->ptr_env;
	while (env[k])
	{
		l = 0;
		if (str[i] == env[k][l])
		{
			while (env[k][l] && env[k][l] != '=')
				l++;
			while (env[k][l + j])
				j++;
			ft_printf("size var = %d\n", j - 1);
			return (j - 1);
		}
		k++;
	}
	return (0);
}

int	get_name_size(char *str, int i)
{
	while (str[i] && !is_whitespace(str[i]) && is_valid_char(str[i]) && str[i] != '\"'
		&& str[i] != '\'' && str[i] != '|')
		i++;
	ft_printf("size name = %d\n", i - 1);
	return (i - 1);
}

int	size_string(t_cmd *cmd, char *str, int *i, int j)
{
	int	k;
	int	size_name;

	k = 0;
	if ((str[*i] == '\'' || str[*i] == '\"') && str[*i] == str[*i + j])
	{
		j -= 1;
		*i += 1;
	}
	while (str[k])
	{
		if (str[k] == '$' && cmd->quote != 2)
		{
			size_name = get_name_size(str, ++k);
			if (!is_env_var(cmd, str, k))
			{
				j -= size_name;
				continue ;
			}
			j += size_var(cmd, str, k) - size_name;
			continue ;
		}
			k++;
	}
	return (j);
}

char	*word_to_array(char *str, int i, int j, t_cmd **cmd)
{
	int		k;
	char	*tokens;

	if (str)
	{
		j = size_string(*cmd, str, &i, j);
		k = 0;
		tokens = malloc (sizeof(char) * (j + 1));
		if (!tokens)
			end(cmd);
		while (str[i] && k < j)
			tokens[k++] = str[i++];
		tokens[k] = '\0';
	}
	return (tokens);
}

t_dir	*ft_dirnew(t_cmd **cmd)
{
	t_dir	*tmp;

	tmp = malloc(sizeof(t_dir));
	if (!tmp)
		end(cmd);
	tmp->content= NULL;
	tmp->type= 0;
	tmp->left= 0;
	tmp->right= 0;
	tmp->next= NULL;
	return (tmp);
}

t_cmd	*ft_commandnew(char **envp)
{
	t_cmd	*tmp;

	tmp = malloc (sizeof(t_cmd));
	if (!tmp)
		end(NULL);
	tmp->tokens_count = 0;
	tmp->ptr_env = envp;
	tmp->bool_file = 0;
	tmp->dir = NULL;
	tmp->quote = 0;
	tmp->next = NULL;
	return (tmp);
}
