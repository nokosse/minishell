void	parse(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < 'a' && str[i] > 'z') && (str[i] < 'A' && str[i] > 'Z'))
			ft_printf("parse error near")
	}
}

int	check_tokens(t_cmd *cmd)
{
	int		i;
	char	**array;

	i = 0;
	array = cmd->tokens;
	while (array[i])
		i++;
	if (i == 0)
		parse
}
