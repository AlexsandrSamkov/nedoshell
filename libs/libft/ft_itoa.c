/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:10:05 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 04:46:15 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoalen(int long n, size_t sign)
{
	size_t	i;

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

static char	*ft_init_itoa(int *n, size_t *sign, size_t *len, int long	*nb)
{
	char	*s;

	if (*n >= 0)
		*sign = 0;
	else
		*sign = 1;
	*nb = (int long)(*n);
	if (*nb < 0)
		*nb *= -1;
	*len = ft_itoalen(*nb, *sign);
	s = malloc(sizeof(char) * (*len + 1));
	return (s);
}

char	*ft_itoa(int n)
{
	char		*s;
	int long	nb;
	size_t		sign;
	size_t		len;

	s = ft_init_itoa(&n, &sign, &len, &nb);
	if (s)
	{
		s[len--] = 0;
		while (len >= sign)
		{
			if (nb >= 10)
				s[len] = nb % 10 + '0';
			else
				s[len] = nb + '0';
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
