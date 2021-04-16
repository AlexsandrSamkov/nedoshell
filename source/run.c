/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 06:33:33 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 06:50:55 by weambros         ###   ########.fr       */
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

void	ft_run_command_2(t_lstcmds *cmds, t_lstcmds *prev)
{
	ft_open_pipe(cmds, prev);
	if (ft_is_fork(cmds) == 1)
		ft_fork_command(cmds, cmds, prev);
	else if (ft_is_fork(cmds) == 2)
	{
		ft_run_r_in(cmds, prev);
		ft_fork_command(prev, cmds, prev);
	}
	else if (ft_is_fork(cmds) == 3)
		ft_my_bin(cmds);
	if (ft_is_r_out(prev))
		ft_run_r_out(prev->fds[0], cmds->args[0], \
	cmds->args, prev->token);
	ft_close_pipe(cmds, prev);
}

void	ft_run_command(t_lstcmds *cmds)
{
	t_lstcmds	*prev;

	if (!ft_check_error_syntax(cmds))
	{
		while (cmds)
		{
			if (cmds->error < 0)
				ft_run_error(cmds);
			prev = cmds->prev;
			if (prev && prev->token == TOKEN_ANDAND && prev->error != 0)
			{
				cmds = cmds->next;
				continue ;
			}
			if (prev && prev->token == TOKEN_OROR && prev->error == 0)
			{
				cmds = cmds->next;
				continue ;
			}
			ft_run_command_2(cmds, prev);
			cmds = cmds->next;
		}
	}
}