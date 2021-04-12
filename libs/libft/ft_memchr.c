/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:37:11 by weambros          #+#    #+#             */
/*   Updated: 2021/04/09 15:57:57 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*f;

	f = s;
	while (n > 0)
	{
		if (*f == c)
			return ((void *)f);
		f++;
		n--;
	}
	return (0);
}
