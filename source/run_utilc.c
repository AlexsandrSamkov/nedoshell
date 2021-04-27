/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utilc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 01:33:31 by weambros          #+#    #+#             */
/*   Updated: 2021/04/24 18:50:28 by sjennett         ###   ########.fr       */
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
	if ((!ft_strncmp(cmds->args[0], "exit", 5)))
		run = ft_exit(cmds->args);
	if (is_exit && run)
		exit(ft_errno(0, GET));
	if (run)
		ft_errno(ret, SET);
	return (run);
}

void	ft_wait(pid_t pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WTERMSIG(status) == SIGQUIT)
		ft_errno(131, SET);
	else if (WTERMSIG(status) == SIGINT)
		ft_errno(130, SET);
	else if (status)
		ft_errno(WIFEXITED(status), SET);
	else
		ft_errno(0, SET);
}
