/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:33:45 by weambros          #+#    #+#             */
/*   Updated: 2020/11/05 17:42:43 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	unsigned const char *s;
	unsigned char		*lastd;
	unsigned const char *lasts;

	d = dst;
	s = src;
	lastd = d + len - 1;
	lasts = s + len - 1;
	if (!d && !s)
		return (0);
	if (d < s)
		while (len-- > 0)
			*d++ = *s++;
	else
		while (len-- > 0)
			*lastd-- = *lasts--;
	return (dst);
}
