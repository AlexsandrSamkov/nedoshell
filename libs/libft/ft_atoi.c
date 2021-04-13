/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:45:30 by weambros          #+#    #+#             */
/*   Updated: 2021/04/13 01:00:18 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checklong(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long long	n;
	int			sign;

	sign = 1;
	n = 0;
	while (ft_isspace(*str))
		str++;
	while (*str)
	{
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				sign = -1;
			str++;
		}
		while (*str && ft_isdigit(*str))
			n = n * 10 + *str++ - 48;
		if (n < 0)
			return (ft_checklong(sign));
		if (!(ft_isdigit(*str)))
			break ;
	}
	return (n * sign);
}
