/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 19:02:20 by weambros          #+#    #+#             */
/*   Updated: 2020/11/07 20:42:13 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t dst_len;
	size_t i;
	size_t len;

	i = 0;
	dst_len = ft_strlen(dst);
	if (!(len = (dstsize < dst_len ? dstsize : dst_len) + ft_strlen(src)))
		return (0);
	if (dstsize <= dst_len)
		return (len);
	dstsize = dstsize - 1 - dst_len;
	while (dstsize > 0 && src[i] != '\0')
	{
		dst[dst_len++] = src[i++];
		dstsize--;
	}
	dst[dst_len] = '\0';
	return (len);
}
