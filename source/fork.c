/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 06:45:28 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 05:53:06 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lstcmds	*ft_is_run_pipe(t_lstcmds *cmds)
{
	t_lstcmds	*begin;

	begin = cmds;
	while (begin)
	{
		if (begin->token == TOKEN_PIPE || begin->token == TOKEN_R_OUT
			|| begin->token == TOKEN_R_D_OUT || begin->token == TOKEN_R_IN)
			break ;
		begin = begin->next;
	}
	if (begin)
	{
		while (cmds->next)
			cmds = cmds->next;
		return (cmds);
	}
	return (0);
}

void	ft_pipe(t_lstcmds *cmds, t_lstcmds *prev)
{
	if (prev && (prev->token == TOKEN_R_D_OUT || prev->token == TOKEN_R_OUT))
	{
		pipe(prev->fds);
		close(prev->fds[0]);
	}
	if (prev && (prev->token == TOKEN_PIPE || prev->token == TOKEN_R_IN))
		pipe(prev->fds);
	if (cmds->token == TOKEN_R_IN)
	{
		close(cmds->fds[1]);
	}
}

void	ft_dup2(t_lstcmds *cmds, t_lstcmds *prev)
{
	if (prev && prev->token == TOKEN_R_IN)
		dup2(prev->fds[1], 1);
	if (cmds->token == TOKEN_R_IN)
		dup2(cmds->fds[0], 0);
	if (cmds->token == TOKEN_R_D_OUT || cmds->token == TOKEN_R_OUT)
	{
		dup2(cmds->fds[1], 1);
		close(cmds->fds[1]);
	}
	if (prev && prev->token == TOKEN_PIPE)
	{	
		dup2(prev->fds[0], 0);
		close(prev->fds[0]);
		close(prev->fds[1]);
	}
	if (cmds->token == TOKEN_PIPE)
	{	
		dup2(cmds->fds[1], 1);
		close(cmds->fds[0]);
		close(cmds->fds[1]);
	}	
}

pid_t *ft_pid_mass(char c, pid_t value)
{
	static pid_t *mass;
	static int i;

	if (c == INIT)
	{
		i = 0;
		mass = ft_calloc(2024,sizeof (pid_t));
		if (!mass)
			ft_exit_fatal(MSG_ERR_NO_MALLOC);
	}
	if (c == SET)
		mass[i++] = value;
	if (c == DEL)
	{
		i = 0;
		ft_bzero(mass, 2024 * sizeof(pid_t));
	}
	if (c == GET)
		return (mass);
	return (mass);
}

void	ft_run_pipe2(t_lstcmds **cmd, char **env)
{
	t_lstcmds	*cmds;
	t_lstcmds	*prev;

	cmds = *cmd;
	prev = cmds->prev;
	gl_pid = fork();
	if (!gl_pid)
	{
//		ft_putnbr_fd((int)gl_pid, 2);
//		write(2,"\n",1);
		ft_dup2(cmds, prev);
		ft_run(cmds, prev, env);
		exit(0);
	}
	else
	{
		ft_pid_mass(SET,gl_pid);
		if (prev && prev->token == TOKEN_PIPE)
			close(prev->fds[0]);
		if (cmds->token == TOKEN_PIPE)
			close(cmds->fds[1]);

		cmds = cmds->prev;
	}

	*cmd = cmds;
}

void	ft_run_pipe(t_lstcmds *cmds, char **env)
{
	t_lstcmds	*begin;
	t_lstcmds	*prev;
	begin = cmds;
	//gl_pid = 0;
	while (cmds)
	{
		prev = cmds->prev;
		ft_pipe(cmds, prev);
		if (prev && (prev->token == TOKEN_R_D_OUT \
			|| prev->token == TOKEN_R_OUT))
		{
			ft_run_r(cmds, prev);
			cmds = cmds->prev;
			continue ;
		}
		if (ft_run_error(cmds))
		{
			cmds = cmds->prev;
			continue ;
		}
		ft_run_pipe2(&cmds, env);
	}
	pid_t *mass;
	int i = 0;
	mass = ft_pid_mass(GET,0);
	while (mass[i])
		ft_wait(mass[i++]);
	ft_pid_mass(DEL,0);
	ft_close_all_pipe(cmds);

}
