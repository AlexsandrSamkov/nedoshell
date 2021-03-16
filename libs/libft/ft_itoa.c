/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:10:05 by weambros          #+#    #+#             */
/*   Updated: 2020/11/08 16:38:23 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoalen(int long n, size_t sign)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i + sign);
}

char			*ft_itoa(int n)
{
	char		*s;
	int long	nb;
	size_t		sign;
	size_t		len;

	sign = n >= 0 ? (0) : (1);
	nb = (int long)n;
	nb = (nb < 0) ? -(nb) : (nb);
	len = ft_itoalen(nb, sign);
	if ((s = malloc(sizeof(char) * (len + 1))))
	{
		s[len--] = 0;
		while (len >= sign)
		{
			s[len] = nb >= 10 ? (nb % 10 + '0') : (nb + '0');
			if (len == 0)
				break ;
			len--;
			nb = nb / 10;
		}
		if (sign)
			s[len] = '-';
	}
	return (s);
}
