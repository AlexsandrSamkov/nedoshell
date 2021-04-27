/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 04:48:05 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 06:09:39 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_mass(char **mas)
{
	int	i;

	i = 0;
	if (!mas)
		return (0);
	while (mas[i])
		i++;
	return (i);
}

char	**ft_get_mas(int count)
{
	char	**res;

	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	return (res);
}

void	ft_strjoin_index_get(char *s1, char *s2, char **res, int start)
{
	int	len;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	len = (int)(ft_strlen(s1) + ft_strlen(s2));
	*res = (char *)malloc(len + 1);
	if (!*res)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	while (i < len)
	{
		while (k < (int)ft_strlen(s2) && i >= start)
			res[0][i++] = s2[k++];
		if (i >= len)
			break ;
		res[0][i++] = s1[j++];
	}
	res[0][i] = '\0';
}

char	*ft_strjoin_index(char **s1, char **s2, int *start)
{
	char	*res;
	char	*tmp;

	tmp = s1[0];
	if (!s1[0])
		return (0);
	if (!s2[0])
	{
		res = ft_strdup(s1[0]);
		if (!res)
			ft_exit_fatal(MSG_ERR_NO_MALLOC);
		tmp = ft_free(tmp);
		return (res);
	}
	ft_strjoin_index_get(s1[0], s2[0], &res, *start);
	tmp = ft_free(tmp);
	s2[0] = ft_free(s2[0]);
	return (res);
}
