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

int	ft_run_bin(t_lstcmds *cmds)
{
	if (!ft_strncmp(cmds->args[0], "env", 4))
	{
		ft_env(0, 0, ALL);
		return (1);
	}
	else if (!ft_strncmp(cmds->args[0], "pwd", 4))
	{
		ft_pwd();
		return (1);
	}
	else if (!ft_strncmp(cmds->args[0], "echo", 5))
	{
		ft_echo(cmds->args);
		return (1);
	}
	return (0);
}

void	ft_fork_command(t_lstcmds *cmd, t_lstcmds *cmds, t_lstcmds *prev)
{
	int			status;
	char		**env_mass;
	t_lstenv	*env;

	g_pid = fork();
	ft_env(&env, 0, GET_ENV);
	env_mass = ft_get_env_mass(env);
	if (!g_pid)
	{
		ft_dup2(cmds, prev);
		if (!ft_run_bin(cmds))
			execve(cmd->args[0], cmd->args, env_mass);
		exit(0);
	}
	waitpid(g_pid, &status, 0);
	ft_free_mas(&env_mass);
	cmds->error = status;
	if (status > 0)
		ft_errno(1, SET);
	else if (status == 0)
		ft_errno(0, SET);
}
