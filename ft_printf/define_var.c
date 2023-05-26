/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:24:25 by operez            #+#    #+#             */
/*   Updated: 2023/01/17 15:06:48 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	define_var(const char *s, t_print *tab)
{
	if (*s != 'c' && *s != 's' && *s != 'p' && *s != 'd' && *s != 'i'
		&& *s != 'u' && *s != 'x' && *s != 'X' && *s != '%')
		return (-1);
	if (*s == 'c')
		print_char(tab);
	else if (*s == 's')
		print_string(tab);
	else if (*s == 'p')
		print_ptr(tab);
	else if (*s == 'd' || *s == 'i')
		print_decimal(tab);
	else if (*s == 'u')
		print_unsigned_d(tab);
	else if (*s == 'x')
		print_low_hex(tab);
	else if (*s == 'X')
		print_up_hex(tab);
	else if (*s == '%')
		print_percent(tab);
	return (0);
}
