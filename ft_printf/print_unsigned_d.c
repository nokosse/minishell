/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:03:21 by operez            #+#    #+#             */
/*   Updated: 2023/01/16 17:31:34 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_aff_unsigned(unsigned int n, t_print *tab)
{	
	unsigned int	nb;

	nb = n;
	if (nb > 9)
		ft_aff_unsigned(nb / 10, tab);
	nb = nb % 10 + '0';
	tab->ret += write (1, &nb, 1);
}

void	print_unsigned_d(t_print *tab)
{
	unsigned int	u;

	u = va_arg(tab->arg_ptr, unsigned int);
	ft_aff_unsigned(u, tab);
}
