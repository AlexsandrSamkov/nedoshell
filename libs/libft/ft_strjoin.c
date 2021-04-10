/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 20:48:13 by weambros          #+#    #+#             */
/*   Updated: 2021/04/09 16:24:31 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*pstr;
	int		len;

	len = 0;
	if (!s1 && !s2)
		return (0);
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s1);
	str = malloc(1 + len);
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
