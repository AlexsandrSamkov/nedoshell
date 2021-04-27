/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 06:33:33 by weambros          #+#    #+#             */
/*   Updated: 2021/04/24 18:51:41 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_no_fork(char *s)
{
	if (!s)
		return (0);
	if ((!ft_strncmp("unset", s, ft_strlen(s)) && ft_strlen(s) == 5)
		|| (!ft_strncmp("UNSET", s, ft_strlen(s)) && ft_strlen(s) == 5)
		|| (!ft_strncmp("export", s, ft_strlen(s)) && ft_strlen(s) == 6)
		|| (!ft_strncmp("EXPORT", s, ft_strlen(s)) && ft_strlen(s) == 6)
		|| (!ft_strncmp("cd", s, ft_strlen(s)) && ft_strlen(s) == 2)
		|| (!ft_strncmp("exit", s, ft_strlen(s)) && ft_strlen(s) == 4)
		|| (!ft_strncmp("CD", s, ft_strlen(s)) && ft_strlen(s) == 2))
		return (1);
	return (0);
}

void	ft_run_excve(t_lstcmds *cmds, char **env)
{
	if (!cmds->args)
		exit(0);
	if (!ft_run_bin(cmds, 1))
		execve(cmds->args[0], cmds->args, env);
}

void	ft_close_all_pipe_1(t_lstcmds *cmds)
{
	while (cmds)
	{
		if (cmds->fds[1] > 0)
			close(cmds->fds[1]);
		if (cmds->fds[0] > 0)
			close(cmds->fds[0]);
		cmds = cmds->prev;
	}
}

void	ft_run(t_lstcmds *cmds, t_lstcmds *prev, char **env)
{
	if (prev && prev->token == TOKEN_R_IN)
		ft_run_r_in(cmds);
	else
		ft_run_excve(cmds, env);
}

void	ft_run_command(t_lstcmds *cmds)
{
	t_lstcmds	*pipe;
	char		**env;

	env = ft_get_env_mass();
	if (ft_check_error_syntax(cmds))
		return ;
	pipe = ft_is_run_pipe(cmds);
	if (pipe)
		ft_run_pipe(pipe, env);
	else if (!ft_run_error(cmds) && !ft_run_bin(cmds, 0))
	{
		ft_fix_signal_quit(cmds->args[0]);
		g_pid = fork();
		if (!g_pid)
		{
			execve(cmds->args[0], cmds->args, env);
			exit(0);
		}
		ft_wait(g_pid);
	}
	ft_free_mas(&env);
}
