/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:14:22 by weambros          #+#    #+#             */
/*   Updated: 2020/11/08 16:37:04 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_set(const char c, char const *set)
{
	size_t i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	size_t	ft_upset(char const *s1, char const *set)
{
	size_t upset;
	size_t i;

	upset = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_set(s1[i], set) == 0)
			return (upset);
		i++;
		upset++;
	}
	return (upset);
}

static	size_t	ft_downset(char const *s1, char const *set)
{
	size_t downset;
	size_t i;

	downset = 0;
	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		if (ft_set(s1[i], set) == 0)
			return (downset);
		i--;
		downset++;
	}
	return (downset);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*result;
	size_t	up;
	size_t	down;
	size_t	len;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	up = ft_upset(s1, set);
	down = ft_downset(s1, set);
	if (up == len)
		return (ft_strdup(""));
	if (!(str = ft_calloc(sizeof(char), len + 1 - up - down)))
		return (0);
	result = str;
	while (up < len - down)
		*str++ = s1[up++];
	*str = '\0';
	return (result);
}
