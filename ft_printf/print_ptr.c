/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:08:03 by operez            #+#    #+#             */
/*   Updated: 2023/01/17 15:08:43 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putnbr_base3(unsigned long nbr, char *base, t_print *tab)
{
	unsigned long	n;

	n = nbr;
	if (n >= 16)
		ft_putnbr_base3(n / 16, base, tab);
	n = n % 16;
	tab->ret += write(1, &(base[n]), 1);
}

void	print_ptr(t_print *tab)
{
	unsigned long	p;

	p = va_arg(tab->arg_ptr, unsigned long);
	if (p == 0)
	{
		write (1, "(nil)", 5);
		tab->ret += 5;
	}
	else
	{
		write (1, "0x", 2);
		tab->ret += 2;
		ft_putnbr_base3(p, "0123456789abcdef", tab);
	}
}
