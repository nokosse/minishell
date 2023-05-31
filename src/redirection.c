#include "../minishell.h"
/*
void	ignore_param(t_cmd *cmd, char *str, int *i)
{
	if (str[*i] == '<')
	{

	}
}
*/
void	set_dir_struct(t_cmd **cmd, char *str, int *i)
{
	if (str[*i] == '<')
	{
		if (is_whitespace(str[*i + 1]))
		{
			(*cmd)->dir->left = 1;
			*i += 1;
		}
		if (str[*i + 1] == '<' && is_whitespace(str[*i + 2]))
		{
			(*cmd)->dir->left = 1;
			(*cmd)->dir->r_double = 1;
			*i += 2;
		}
	}
	else if (str[*i] == '>')
	{
		if (is_whitespace(str[*i + 1]))
		{
			(*cmd)->dir->right= 1;
			*i += 1;
		}
		if (str[*i + 1] == '<' && is_whitespace(str[*i + 2]))
		{
			(*cmd)->dir->right= 1;
			(*cmd)->dir->r_double = 1;
			*i += 2;
		}
	}

}
void	handle_redirection(t_cmd **cmd, char *str, int *i)
{
	int	j;

	j = 0;
	if ((*cmd)->bool_file == 1)
	{
		(*cmd)->dir->next = ft_dirnew(cmd);
		(*cmd)->dir = (*cmd)->dir->next;
	}
	set_dir_struct(cmd, str, i);
	while (str[*i] && is_whitespace(str[*i]))
		i++;
	while (str[*i + j] && !(is_whitespace(str[*i + j])) && str[*i + j + 1] != '|')
		j++;
	if ((str[*i + j]) != '\0')
		(*cmd)->dir->content = word_to_array(str, *i, j);
}

