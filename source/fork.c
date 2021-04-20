/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 06:45:28 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 06:51:02 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_get_pipe_data_fix(char **data, int *bytes)
{
	int		len;
	char	*tmp;
	int		i;

	if (*bytes == 0)
		return ;
	len = ft_strlen(*data);
	if (len == 0)
		return ;
	if (data[0][len - 1] != '\n')
		return ;
	tmp = malloc(len + 1);
	if (!tmp)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	i = 0;
	while (i < len - 1)
	{
		tmp[i] = data[0][i];
		i++;
	}
	tmp[i] = '\0';
	ft_free(data[0]);
	data[0] = tmp;
	(*bytes)--;
}

int	ft_get_pipe_data(int fd, char **data)
{
	int		byte;
	int		bytes;
	char	*buf;
	char	*tmp;

	buf = malloc(2);
	ft_check_str_fatal(buf);
	bytes = 0;
	byte = read(fd, buf, 1);
	while (byte > 0)
	{
		bytes += byte;
		buf[1] = '\0';
		tmp = *data;
		*data = ft_strjoin(*data, buf);
		ft_check_str_fatal(*data);
		tmp = ft_free(tmp);
		byte = read(fd, buf, 1);
	}
	ft_get_pipe_data_fix(data, &bytes);
	if (byte < 0)
		return (-1);
	buf = ft_free(buf);
	return (bytes);
}

int	ft_run_bin(t_lstcmds *cmds, int is_exit)
{
	int ret;
	int run;

	run = 0;
	ret = 0;
	if (!ft_strncmp(cmds->args[0], "env", 4))
	{
		ft_env(0, 0, ALL);
		ret = 1;
	}
	else if (!ft_strncmp(cmds->args[0], "pwd", 4))
	{
		ret = ft_pwd();
		run = 1;
	}
	else if (!ft_strncmp(cmds->args[0], "echo", 5))
	{
		ret = ft_echo(cmds->args);
		run = 1;
	}
	else if (!ft_strncmp(cmds->args[0],"unset", 6))
	{
		ret = ft_unset(cmds->args);
		run = 1;
	}
	else if (!ft_strncmp(cmds->args[0],"export", 7))
	{
		ret = ft_export(cmds->args);
		run = 1;
	}
	else if ((!ft_strncmp(cmds->args[0],"cd", 3)))
	{
		ret = ft_cd(cmds->args);
		run = 1;
	}
	if (is_exit && run)
		exit(ret);
	if (run)
		ft_errno(ret,SET);
	return (run);
}

