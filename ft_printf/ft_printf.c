/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:07:23 by operez            #+#    #+#             */
/*   Updated: 2023/01/19 18:38:57 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	t_print	tab;

	tab.ret = 0;
	va_start(tab.arg_ptr, s);
	while (s && *s)
	{
		while (*s && *s != '%')
			tab.ret += write (1, s++, 1);
		if (*s == '%')
			define_var(++s, &tab);
		if (*s != '\0')
			s++;
	}
	va_end(tab.arg_ptr);
	return (tab.ret);
}
