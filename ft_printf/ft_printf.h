/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: operez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:35:37 by operez            #+#    #+#             */
/*   Updated: 2023/01/17 15:09:27 by operez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_print
{
	va_list			arg_ptr;
	unsigned int	ret;

}		t_print;

int		ft_printf(const char *s, ...);
int		define_var(const char *s, t_print *tab);
void	print_char(t_print *tab);
void	print_string(t_print *tab);
void	print_decimal(t_print *tab);
void	print_unsigned_d(t_print *tab);
void	print_low_hex(t_print *tab);
void	print_up_hex(t_print *tab);
void	print_percent(t_print *tab);
void	print_ptr(t_print *tab);

#endif
