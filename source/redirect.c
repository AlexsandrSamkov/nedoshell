/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 03:20:03 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 07:09:29 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_open_r_error2(char *s, struct stat sb, int token, int *ret)
{
	if (!(sb.st_mode & S_IWUSR)
		&& (token == TOKEN_R_D_OUT || token == TOKEN_R_OUT))
	{
		ft_put_error(MSG_ERR_NO_PERM);
		ft_put_error(s);
		ft_put_error("\n");
		*ret = 126;
	}
	if (!(sb.st_mode & S_IRUSR) && token == TOKEN_R_IN)
	{
		ft_put_error(MSG_ERR_NO_PERM);
		ft_put_error(s);
		ft_put_error("\n");
		*ret = 126;
	}
}

int	ft_check_open_r_error(char *s, int token)
{
	struct stat	sb;
	int			ret;

	ret = 0;
	if (!s)
		ret = -1;
	if (stat(s, &sb) == -1)
		ret = -1;
	if (S_IFDIR == (sb.st_mode & S_IFMT) && !ret)
	{
		ft_put_error(MSG_ERR_IS_DIRECT);
		ft_put_error(s);
		ft_put_error("\n");
		ret = 126;
	}
	ft_check_open_r_error2(s, sb, token, &ret);
	return (ret);
}

void	ft_run_r(t_lstcmds *cmds, t_lstcmds *prev)
{
	if (!prev)
		return ;
	if (!ft_check_open_r_error(cmds->args[0], prev->token))
	{
		if (prev->token == TOKEN_R_OUT)
			prev->fds[1] = \
			open(cmds->args[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (prev->token == TOKEN_R_D_OUT)
			prev->fds[1] = \
			open(cmds->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (prev->fds[1] < 0)
			ft_errno(1, SET);
		ft_errno(0, SET);
	}
	else
		ft_errno(1, SET);
}

void	ft_run_r_in2(t_lstcmds *cmds, char *buf, int *ret)
{
	int	byte;
	int	fd;

	fd = open(cmds->args[0], O_RDONLY);
	if (fd < 0)
	{
		ft_put_error(MSG_ERR_NO_OPEN);
		*ret = 127;
	}
	byte = (int)read(fd, buf, 1);
	while (byte > 0)
	{
		if (write(1, buf, 1) < 0)
			ft_put_error(MSG_ERR_NO_WRITE);
		byte = (int)read(fd, buf, 1);
	}
	close(fd);
}

void	ft_run_r_in(t_lstcmds *cmds)
{
	char	*buf;
	int		ret;

	ret = 0;
	buf = malloc(1);
	if (!buf)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	ret = ft_check_open_r_error(cmds->args[0], TOKEN_R_IN);
	if (!ret)
		ft_run_r_in2(cmds, buf, &ret);
	buf = ft_free(buf);
	exit(ret);
}
