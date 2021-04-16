/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 05:21:22 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 05:51:16 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*pstr;
	size_t	len;

	if (!s1 && !s2)
		return (0);
	len = 0;
	if (s1)
		len = len + ft_strlen(s1);
	if (s2)
		len = len + ft_strlen(s2);
	str = ft_calloc(1, len + 1);
	if (!str)
		return (0);
	pstr = str;
	if (s1)
		while (*s1)
			*pstr++ = *s1++;
	if (s2)
		while (*s2)
			*pstr++ = *s2++;
	*pstr = '\0';
	return (str);
}
