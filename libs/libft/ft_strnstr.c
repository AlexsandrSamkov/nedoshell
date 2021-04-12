/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:24:32 by weambros          #+#    #+#             */
/*   Updated: 2021/04/09 15:21:52 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t slen)
{
	size_t	find_len;
	char	*h;
	char	*n;
	size_t	i;

	h = (char *)haystack;
	n = (char *)needle;
	i = 0;
	find_len = ft_strlen(n);
	if (!find_len || ft_strncmp(h, n, find_len) == 0)
		return ((char *)haystack);
	if (find_len == slen)
		return (0);
	while (i < slen && *h)
	{
		if (i + find_len > slen)
			return (0);
		if (ft_strncmp(h, n, find_len) == 0)
			return (h);
		h++;
		i++;
	}
	return (0);
}
