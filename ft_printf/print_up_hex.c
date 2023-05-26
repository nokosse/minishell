/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_up_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:46:58 by operez            #+#    #+#             */
/*   Updated: 2023/01/16 17:31:18 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putnbr_base2(unsigned int nbr, char *base, t_print *tab)
{
	long	n;

	n = nbr;
	if (n >= 16)
		ft_putnbr_base2(n / 16, base, tab);
	n = n % 16;
	tab->ret += write(1, &(base[n]), 1);
}

void	print_up_hex(t_print *tab)
{
	unsigned int	x;

	x = va_arg(tab->arg_ptr, unsigned int);
	ft_putnbr_base2(x, "0123456789ABCDEF", tab);
}
