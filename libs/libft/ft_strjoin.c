/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 20:48:13 by weambros          #+#    #+#             */
/*   Updated: 2020/12/01 18:45:20 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *str;
	char *pstr;

	if (!s1 && !s2)
		return (0);
	if (!(str = malloc(sizeof(char) * (1 + (s1 ? ft_strlen(s1) : 0)
	+ (s2 ? ft_strlen(s2) : 0)))))
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
