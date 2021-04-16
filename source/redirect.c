/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 03:20:03 by weambros          #+#    #+#             */
/*   Updated: 2021/04/15 04:06:57 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_run_r_in(t_lstcmds *cmds, t_lstcmds *prev)
{
	int		fd;
	int		byte;
	int		bytes;
	char	buf[2];
	char	*s;

	s = 0;
	bytes = 0;
	fd = open(cmds->args[0], O_RDONLY);
	byte = read(fd, buf, 1);
	while (byte > 0)
	{
		buf[1] = '\0';
		ft_strjoin_and_free(&s, buf);
		ft_check_str_fatal(s);
		bytes += byte;
		byte = read(fd, buf, 1);
	}
	if (byte < 0)
		printf("fatal"); // ошибку
	if (write(prev->fds[1], s, bytes) < 0)
		ft_exit_fatal(MSG_ERR_NO_WRITE);
	close(prev->fds[1]);
	ft_free(s);
	return (s);
}

int	ft_check_open_r_error(char *s, int token)
{
	struct stat	sb;

	if (!s)
		return (1);
	if (stat(s, &sb) == -1)
		return (0);
	if (S_IFDIR == (sb.st_mode & S_IFMT))
	{
		write(2, MSG_ERR_IS_DIRECT, ft_strlen(MSG_ERR_IS_DIRECT));
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
		return (1);
	}
	else if (!(sb.st_mode & S_IWUSR))
	{
		write(2, MSG_ERR_NO_PERM, ft_strlen(MSG_ERR_NO_PERM));
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
		return (1);
	}
	(void)token;
	return (0);
}

int	ft_run_r_out(int pipefd, char *filename, char **args, int token)
{
	int		fd;
	int		count;
	char	*data;
	int		i;

	data = 0;
	if (ft_check_open_r_error(filename, token))
		return (0);
	if (token == TOKEN_R_OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (-1);
	count = ft_get_pipe_data(pipefd, &data);
	if (count < 0)
		return (-1);
	if (0 > write(fd, data, count))
		ft_exit_fatal(MSG_ERR_NO_WRITE);
	i = 1;
	while (args[i])
	{
		if (data && ft_strlen(data))
			if (0 > write(fd, " ", 1))
				ft_exit_fatal(MSG_ERR_NO_WRITE);
		if (0 > write(fd, args[i], ft_strlen(args[i])))
			ft_exit_fatal(MSG_ERR_NO_WRITE);
		if (!(args[i + 1] == 0))
			if (0 > write(fd, " ", 1))
				ft_exit_fatal(MSG_ERR_NO_WRITE);
		i++;
	}
	if (0 > write(fd, "\n", 1))
		ft_exit_fatal(MSG_ERR_NO_WRITE);
	close(fd);
	return (0);
}