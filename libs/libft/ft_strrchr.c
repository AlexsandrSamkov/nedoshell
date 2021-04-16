/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:44:13 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 04:19:44 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*find;
	char	*p;

	find = 0;
	if (c == '\0')
		return (ft_strchr(s, c));
	p = ft_strchr(s, c);
	while (p != 0)
	{
		find = p;
		s = p + 1;
		p = ft_strchr(s, c);
	}
	return (find);
}
