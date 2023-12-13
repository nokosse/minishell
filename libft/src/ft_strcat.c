/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:22:08 by kevso             #+#    #+#             */
/*   Updated: 2023/12/13 20:22:34 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = dest;
	while (tmp[i])
		i++;
	while (src[j])
	{
		tmp[i] = src[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (dest);
}
