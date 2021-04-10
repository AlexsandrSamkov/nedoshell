/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 08:31:59 by weambros          #+#    #+#             */
/*   Updated: 2021/04/09 16:11:11 by weambros         ###   ########.fr       */
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

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	len = read(fd, buff, BUFFER_SIZE);
	while (len > 0)
	{
		buff[len] = '\0';
		tmp = *save;
		*save = ft_strjoin(*save, buff);
		if (!*save)
		{
			ft_free(&tmp, 0);
			return (ft_free(&buff, -1));
		}
		ft_free(&tmp, 0);
		if (ft_strchr(buff, '\n'))
			break ;
		len = read(fd, buff, BUFFER_SIZE);
	}
	return (ft_free(&buff, len));
}

static int	ft_check_line(char **line, char **save)
{
	char	*check;
	char	*tmp;

	check = ft_strchr(*save, '\n');
	if (check)
	{
		*check = '\0';
		*line = ft_strdup(*save);
		if (!*line)
			return (-1);
		tmp = *save;
		*save = (ft_strdup(++check));
		if (!*save)
			return (ft_free(&tmp, -1));
		return (ft_free(&tmp, 1));
	}
	*line = ft_strdup(*save);
	if (!*line)
		return (ft_free(&*save, -1));
	return (ft_free(&*save, 0));
}

int	get_next_line(int fd, char **line)
{
	static char	*save[4048];
	int			len;

	if (!line || BUFFER_SIZE <= 0 || fd < 0 || fd > 4048)
		return (-1);
	len = ft_read_line(&save[fd], fd);
	if (len == -1)
		return (-1);
	if (len == 0 && save[fd] == 0)
	{
		*line = ft_strdup("");
		if (!*line)
			return (-1);
		return (ft_free(&save[fd], 0));
	}
	return (ft_check_line(&*line, &save[fd]));
}
