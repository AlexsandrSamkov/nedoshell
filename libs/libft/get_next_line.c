/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 08:31:59 by weambros          #+#    #+#             */
/*   Updated: 2020/11/25 06:52:35 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_free(char **s, int res)
{
	if (*s == 0)
		return (res);
	free(*s);
	*s = 0;
	return (res);
}

static int	ft_read_line(char **save, int fd)
{
	char	*buff;
	char	*tmp;
	int		len;

	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((len = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[len] = '\0';
		tmp = *save;
		if (!(*save = ft_strjoin(*save, buff)))
		{
			ft_free(&tmp, 0);
			return (ft_free(&buff, -1));
		}
		ft_free(&tmp, 0);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (ft_free(&buff, len));
}

static int	ft_check_line(char **line, char **save)
{
	char	*check;
	char	*tmp;

	if ((check = ft_strchr(*save, '\n')))
	{
		*check = '\0';
		if (!(*line = ft_strdup(*save)))
			return (-1);
		tmp = *save;
		if (!(*save = (ft_strdup(++check))))
			return (ft_free(&tmp, -1));
		return (ft_free(&tmp, 1));
	}
	if (!(*line = ft_strdup(*save)))
		return (ft_free(&*save, -1));
	return (ft_free(&*save, 0));
}

int			get_next_line(int fd, char **line)
{
	static char	*save[4048];
	int			len;

	if (!line || BUFFER_SIZE <= 0 || fd < 0 || fd > 4048)
		return (-1);
	if ((len = ft_read_line(&save[fd], fd)) == -1)
		return (-1);
	if (len == 0 && save[fd] == 0)
	{
		if (!(*line = ft_strdup("")))
			return (-1);
		return (ft_free(&save[fd], 0));
	}
	return (ft_check_line(&*line, &save[fd]));
}
