/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 06:33:33 by weambros          #+#    #+#             */
/*   Updated: 2021/04/20 05:31:40 by weambros         ###   ########.fr       */
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

t_lstcmds	*ft_is_run_pipe(t_lstcmds *cmds)
{
	t_lstcmds	*begin;

	begin = cmds;
	while (begin)
	{
		if (begin->token == TOKEN_PIPE || begin->token == TOKEN_R_OUT
			|| begin->token == TOKEN_R_D_OUT || begin->token == TOKEN_R_IN)
			break;
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

void ft_pipe(t_lstcmds *cmds, t_lstcmds *prev)
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
	if (cmds->token == TOKEN_PIPE)
	{
		close(cmds->fds[0]);
	}
}

void ft_dup2(t_lstcmds *cmds, t_lstcmds *prev)
{
	if (prev && prev->token == TOKEN_R_IN)
	{
		dup2(prev->fds[1], 1);
		ft_putendl_fd("hello\n",2);
	}
	if (cmds->token == TOKEN_R_IN)
			dup2(cmds->fds[0],0);
	if (cmds->token == TOKEN_R_D_OUT || cmds->token == TOKEN_R_OUT)
	{
		dup2(cmds->fds[1],1);
		close(cmds->fds[1]);
		ft_putendl_fd(cmds->args[0],2);
	}
	if (prev && prev->token == TOKEN_PIPE)
	{
			dup2(prev->fds[0],0);
			close(prev->fds[1]);
			close(prev->fds[0]);
	}
	if (cmds->token == TOKEN_PIPE)
	{
			dup2(cmds->fds[1],1);
			close(cmds->fds[0]);
			close(cmds->fds[1]);
	}	
}

void ft_run_rtest(t_lstcmds *cmds,t_lstcmds *prev)
{
	if (prev->token == TOKEN_R_OUT)
		prev->fds[1] = open(cmds->args[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (prev->token == TOKEN_R_D_OUT)
		prev->fds[1] = open(cmds->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (prev->fds[1] < 0)
		return;//"ошибка"
}

void ft_run_excve(t_lstcmds *cmds)
{
	char		**env_mass;
	env_mass = ft_get_env_mass();
	if (!ft_run_bin(cmds, 1))
		execve(cmds->args[0],cmds->args,env_mass);
}

void ft_run_r_int(t_lstcmds *cmds)
{
	int		fd;
	char 	*buf;
	int 	byte;

	t_lstcmds *prev;
	prev = cmds->prev;
	buf = malloc(1);
	if (!buf)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	fd = open(cmds->args[0],O_RDONLY);
	byte = (int)read(fd,buf,1);
	while (byte > 0)
	{
		write(1,buf,1);
		byte = (int)read(fd,buf,1);
	}
	exit(0);
}
void ft_runtest(t_lstcmds *cmds, t_lstcmds *prev)
{

	if (prev && prev->token == TOKEN_R_IN)
		ft_run_r_int(cmds);
	else
		ft_run_excve(cmds);
}

void ft_run_pipe(t_lstcmds *cmds)
{
	t_lstcmds  *begin;
	t_lstcmds *prev;
	pid_t pid;
	int status;
	begin = cmds;
	pid = 0;
	while (cmds)
	{
		prev = cmds->prev;
		ft_pipe(cmds,prev);
		if (prev && (prev->token == TOKEN_R_D_OUT || prev->token == TOKEN_R_OUT))
		{
			ft_run_rtest(cmds, prev);
			cmds = cmds->prev;
			continue;
		}
		if (ft_run_error(cmds))
		{
			cmds = cmds->prev;
			continue;
		}
		pid = fork();
		if (!pid)
		{
			ft_dup2(cmds,prev);
			ft_runtest(cmds, prev);
			exit(0);
		}
		else
			cmds = cmds->prev;
	}
		waitpid(pid,&status,0);
		if (pid != 0)
			ft_errno(1, SET);
	while (begin)
	{
		if (begin->fds[1] > 0)
			close(begin->fds[1]);
		if (begin->fds[0] > 0)
			close(begin->fds[0]);
		begin = begin->prev;
	}
}

void ft_run_command2(t_lstcmds *cmds)
{
	t_lstcmds *pipe;
	char **env;
	int status;
	pid_t pid;
	if (ft_check_error_syntax(cmds))
		return;
	env = ft_get_env_mass();
	signal (SIGQUIT, SIG_IGN);
	pipe = ft_is_run_pipe(cmds);
	if (pipe)
		ft_run_pipe(pipe);
	else
	{
		if (!ft_run_error(cmds))

		if (!ft_run_bin(cmds,0))
		{
			pid = fork();
			if(!pid)
			{
				execve(cmds->args[0], cmds->args, env);
				exit(0);
			}
			waitpid(pid,&status,0);
			if (status > 0)
				ft_errno(1,SET);
		}
	}
	ft_free_mas(&env);
}