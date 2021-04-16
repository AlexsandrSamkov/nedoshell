/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:38:34 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 05:31:43 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (s && f && str)
	{
		i = 0;
		while (s[i])
		{	
			str[i] = f(i, s[i]);
			i++;
		}
		str[i] = '\0';
	}
	else
		return (0);
	return (str);
}
