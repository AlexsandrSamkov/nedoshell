/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:10:05 by weambros          #+#    #+#             */
/*   Updated: 2021/04/09 16:51:35 by weambros         ###   ########.fr       */
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

static void	ft_itoa_newnorm(char **s, int sign, int len, int nb)
{
	s[0][len--] = 0;
	while (len >= sign)
	{
		if (nb >= 10)
			s[0][len] = nb % 10 + '0';
		else
			s[0][len] =  nb + '0';
		if (len == 0)
			break ;
		len--;
		nb = nb / 10;
	}
	if (sign)
		s[0][len] = '-';
}

char	*ft_itoa(int n)
{
	char		*s;
	int long	nb;
	size_t		sign;
	size_t		len;

	if (n >= 0)
		sign = 0;
	else
		sign = 1;
	nb = (int long)n;
	if (nb < 0)
		nb = -nb;
	len = ft_itoalen(nb, sign);
	s = malloc(sizeof(char) * (len + 1));
	if (s)
	{
		ft_itoa_newnorm(&s, sign, len, nb);
	}
	else
		return (0);
	return (s);
}
