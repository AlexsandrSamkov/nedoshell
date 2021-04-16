/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 03:46:47 by weambros          #+#    #+#             */
/*   Updated: 2021/04/15 03:50:38 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_free(void *s)
{
	if (s)
	{
		free(s);
		s = 0;
	}
	return (0);
}

void	ft_free_mas(char ***mas)
{
	char	**tmp;

	if (!(*mas))
		return ;
	tmp = *mas;
	while (*tmp)
	{
		*tmp = (char *)ft_free(*tmp);
		tmp++;
	}
	free(*mas);
	*mas = 0;
}

int	ft_return_and_free(void *s, int ret)
{
	s = ft_free(s);
	return (ret);
}

void	ft_strjoin_and_free(char **s1, char *s2)
{
	char	*tmp;

	tmp = 0;
	tmp = *s1;
	*s1 = ft_strjoin(*s1, s2);
	if (!*s1)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	tmp = ft_free(tmp);
}
