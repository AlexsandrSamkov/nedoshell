/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:02:34 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 05:05:11 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_splitsize(char const *s, char c)
{
	size_t		size;
	char const	*str;
	int			f;

	f = 1;
	size = 0;
	str = s;
	if (!s)
		return (0);
	while (*str)
	{
		if (*str == c)
			f = 1;
		if (*str != c && f == 1)
		{
			f = 0;
			size++;
		}
		str++;
	}
	return (size);
}

static char	*ft_splitword(char const *s, int start, char c)
{
	size_t	j;
	size_t	i;
	char	*str;

	i = 0;
	j = start;
	while (s[j] != c && s[j++] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	j = 0;
	while (s[start] != c && s[start] != '\0')
		str[j++] = s[start++];
	str[j] = '\0';
	return (str);
}

static char	**ft_splitfree(char **split, size_t j)
{
	split[j] = 0;
	if (split)
	{
		while (*split)
		{
			free(*split);
			*split = 0;
			split++;
		}
	}
	free(split);
	split = 0;
	return (0);
}

static char	**ft_split_init(char const *s, char c, size_t *i, size_t *j)
{
	char	**split;

	*i = 0;
	*j = 0;
	split = (char **)malloc(sizeof(char *) * (ft_splitsize(s, c) + 1));
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	split = ft_split_init(s, c, &i, &j);
	if (!split)
		return (0);
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			split[j] = ft_splitword(s, i, c);
			if (!split)
				return (ft_splitfree(split, j));
			while (s[i] != '\0' && s[i] != c)
				i++;
			j++;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
