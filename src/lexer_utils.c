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
#include "../minishell.h"

void	replace_var(t_cmd **cmd, char **tokens, int *k, int *i)
{
	char	**env;
	char	*str;
	int		j;
	int		l;
	int		index;

	str = *tokens;
	index = (*cmd)->env_line_nbr;
	env = (*cmd)->ptr_env;
	j = 0;
	l = 0;
	while (env[index][j] != '=')
		j++;
	j++;
	while (env[index][j + l])
	{
		str[*k] = env[index][j + l];
		*k += 1;
		l++;
	}
	*i += j;
}

int	is_env_var(t_cmd **cmd, char *str, int i)
{
	char	**env;
	int		j;
	int		k;
	int		save;

	k = 0;
	env = (*cmd)->ptr_env;
	if (is_bracket(str, i, str[i]))
		i++;
	save = i;
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
				(*cmd)->env_line_nbr = k;
				//ft_printf("is env\n");
				return (1);
			}
		}
		k++;
	}
	//ft_printf("is not env\n");
	return (0);
}

int	size_var(t_cmd *cmd, char *str, int i)
{
	int		j;
	int		k;
	int		l;
	int		save;
	char	**env;

	k = 0;
	env = cmd->ptr_env;
	if (is_bracket(str, i, str[i]))
		i++;
	save = i;
	while (env[k])
	{
		l = 0;
		i = save;
		j = 0;
		if (str[i] == env[k][l])
		{
			while (str[i] == env[k][l])
			{
				i++;
				l++;
			}
			if (env[k][l] != '=')
			{
				k++;
				continue ;
			}
			while (env[k][l + j])
				j++;
			//ft_printf("size var = %d\n", j - 1);
			return (j - 1);
		}
		k++;
	}
	return (0);
}

int	get_name_size(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] && !is_whitespace(str[i + j]) && is_valid_char(str[i + j]) && str[i + j] != '\"' && str[i + j] != '\'' && str[i + j] != '|' && str[i + j] != '$')
		j++;
	//ft_printf("Size name = %d\n", j + 1);
	return (j + 1);
}

int	size_string(t_cmd **cmd, char *str, int *i, int j)
{
	int	k;
	int	save;

	k = 0;
	save = j;
	if ((str[*i] == '\'' || str[*i] == '\"') && str[*i] == str[*i + j])
	{
		j -= 1;
		*i += 1;
	}
	while (str[*i + k] && k < save)
	{
		if (str[*i + k] == '$' && (*cmd)->quote != 2)
		{
			if (!is_env_var(cmd, str, *i + k + 1))
			{
				j = j - get_name_size(str, *i + k + 1);
				k++;
				continue ;
			}
			j = j - (get_name_size(str, *i + k + 1) - size_var((*cmd), str, *i + k + 1));
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
		j = size_string(cmd, str, &i, j);
		k = 0;
		//ft_printf("Size malloc = %d\n", j + 1);
		tokens = malloc (sizeof(char) * (j + 1));
		if (!tokens)
			end(cmd);
		while (str[i] && k < j)
		{
			if (str[i] == '$' && (*cmd)->quote != 2)
			{
				if (is_env_var(cmd, str, i + 1)) 
				{
					replace_var(cmd, &tokens, &k, &i);
					continue ;
				}
			}
			tokens[k++] = str[i++];
		}
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
