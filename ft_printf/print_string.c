/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:24:28 by operez            #+#    #+#             */
/*   Updated: 2023/01/17 15:00:13 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_string(t_print *tab)
{
	char	*str;

	str = va_arg(tab->arg_ptr, char *);
	if (!str)
	{
		tab->ret += write(1, "(null)", 6);
		return ;
	}
	else
	{
		while (*str)
			tab->ret += write(1, str++, 1);
	}
}
