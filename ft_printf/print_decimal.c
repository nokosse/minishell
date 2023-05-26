/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:41:54 by operez            #+#    #+#             */
/*   Updated: 2023/01/16 17:29:04 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdio.h>

void	ft_putnbr(int n, t_print *tab)
{	
	long long	nb;

	nb = n;
	if (nb < 0)
	{
		tab->ret += write(1, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr(nb / 10, tab);
	nb = nb % 10 + '0';
	tab->ret += write (1, &nb, 1);
}

void	print_decimal(t_print *tab)
{
	int	d;

	d = va_arg(tab->arg_ptr, int);
	ft_putnbr(d, tab);
}
