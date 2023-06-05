/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:17:31 by kvisouth          #+#    #+#             */
/*   Updated: 2023/06/05 12:10:23 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// This function will check if the flag '-n' is passed to the echo command.
// It will only check the argument [1].
// If the argument [1] is '-n' it will return 1.
// If the argument [1] is not '-n' it will return 0.
int check_flag(char **args)
{
	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
		return (1);
	return (0);
}

// This function will when the command 'echo' is called.
// It will print the arguments passed to it.
// In the case check_flag returns 1 : It will print the args[2] and above.
// And will not print a new line at the end.
// Int the case check_flag returns 0 : It will print the args[1] and above.
// And will print a new line at the end.
//
// echo "a" "b"
// Will print 'a b'
// echo "a""b"
// Will print 'ab'
// Works for multiple arguments.
// echo "a" bc def"g"
// Will print 'a bc defg'
//
// It will print the spaces between the arguments.
int builtin_echo(char **args)
{
	int i;
	int n;

	i = 1;
	n = check_flag(args);
	if (n == 1)
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
