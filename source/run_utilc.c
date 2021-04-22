/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utilc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 01:33:31 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 06:54:37 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_run_bin2(t_lstcmds *cmds, int *ret, int *run)
{
	if (!ft_strncmp(cmds->args[0], "env", 4))
	{
		ft_env(0, 0, ALL);
		*ret = 0;
		*run = 1;
	}
	else if (!ft_strncmp(cmds->args[0], "pwd", 4))
	{
		*ret = ft_pwd();
		*run = 1;
	}
	else if (!ft_strncmp(cmds->args[0], "echo", 5))
	{
		*ret = ft_echo(cmds->args);
		*run = 1;
	}
	else if (!ft_strncmp(cmds->args[0], "unset", 6))
	{
		*ret = ft_unset(cmds->args);
		*run = 1;
	}
	return (*run);
}

int	ft_run_bin(t_lstcmds *cmds, int is_exit)
{
	int	ret;
	int	run;

	run = 0;
	ret = 0;
	if (!ft_run_bin2(cmds, &ret, &run))
	{
		if (!ft_strncmp(cmds->args[0], "export", 7))
		{
			ret = ft_export(cmds->args);
			run = 1;
		}
		else if ((!ft_strncmp(cmds->args[0], "cd", 3)))
		{
			ret = ft_cd(cmds->args);
			run = 1;
		}
	}
	else if ((!ft_strncmp(cmds->args[0], "exit", 5)))
		exit(0);
	if (is_exit && run)
		exit(ft_errno(0, GET));
	if (run)
		ft_errno(ret, SET);
	return (run);
}

void	ft_wait(pid_t pid)
{
	int		status;

	status = 0;
	waitpid(pid,&status,0);
	if (status == 256)
		ft_errno(1, SET);
	else
		ft_errno(status, SET);
}
