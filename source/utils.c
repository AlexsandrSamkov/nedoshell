/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 03:13:48 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 06:09:45 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_del_str_from_str_by_index(char *s, int start, int end)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	res = 0;
	i = 0;
	j = -1;
	if (!s)
		return (0);
	len = end - start;
	if (start == end)
		len = 1;
	if (start == 0 && end == 0)
		len = 0;
	res = (char *)malloc(ft_strlen(s) - len + 1);
	if (!res)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	while (s[++j])
	{
		if (j < start || j >= end)
			res[i++] = s[j];
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup_to_index(char *s, int start, int end)
{
	int		len;
	int		i;
	char	*res;

	res = 0;
	i = 0;
	if (!s)
		return (0);
	len = end - start;
	if (start == end)
		len = 1;
	if (start == 0 && end == 0)
		len = 0;
	res = (char *)malloc(len + 1);
	if (!res)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	while (s[start] && start < end)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

int	ft_nbrlen(long n)
{
	int	i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_putnbr(char *s, int *i, long nbr, char *base)
{
	if (nbr >= 10)
		ft_putnbr(s, i, nbr / 10, base);
	s[(*i)++] = base[nbr % 10];
}

char	*ft_int_to_str(int n)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = ft_nbrlen(n);
	res = malloc(len + 1);
	if (!res)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	ft_putnbr(res, &i, n, "0123456789");
	res[len] = '\0';
	return (res);
}
