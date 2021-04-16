/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utilc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 01:33:31 by weambros          #+#    #+#             */
/*   Updated: 2021/04/15 01:56:23 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_dup2(t_lstcmds *cmds, t_lstcmds *prev)
{
	if (cmds->token == TOKEN_PIPE
		|| cmds->token == TOKEN_R_D_OUT
		|| cmds->token == TOKEN_R_OUT)
		dup2(cmds->fds[1], 1);
	if (prev)
		if (prev->token == TOKEN_PIPE
			|| prev->token == TOKEN_R_IN)
			dup2(prev->fds[0], 0);
}

int	ft_is_fork(t_lstcmds *cmds)
{
	t_lstcmds	*prev;

	prev = cmds->prev;
	if (cmds->error == 2)
		return (3);
	if (cmds->token == TOKEN_R_IN || cmds->error < 0)
		return (0);
	if (prev && (prev->token == TOKEN_ANDAND || prev->token == TOKEN_OROR))
		return (1);
	if (prev)
		if (prev->token == TOKEN_R_OUT
			|| prev->token == TOKEN_R_D_OUT)
			return (0);
	if (prev)
		if (prev->token == TOKEN_R_IN)
			return (2);
	return (1);
}

void	ft_open_pipe(t_lstcmds *cmds, t_lstcmds *prev)
{
	int	ret;

	ret = 0;
	if (prev)
		if (prev->token == TOKEN_R_IN)
			ret = pipe(prev->fds);
	if (ret < 0)
		ft_put_error(MSG_ERR_NO_PIPE);
	if (cmds->token == TOKEN_PIPE
		|| cmds->token == TOKEN_R_OUT
		|| cmds->token == TOKEN_R_D_OUT)
		ret = pipe(cmds->fds);
	if (ret < 0)
		ft_put_error(MSG_ERR_NO_PIPE);
}

void	ft_close_pipe(t_lstcmds *cmds, t_lstcmds *prev)
{
	if (cmds->token == TOKEN_PIPE
		|| cmds->token == TOKEN_R_OUT
		|| cmds->token == TOKEN_R_D_OUT)
		close(cmds->fds[1]);
	if (prev)
		if (prev->token == TOKEN_PIPE
			|| prev->token == TOKEN_R_OUT
			|| prev->token == TOKEN_R_D_OUT
			|| prev->token == TOKEN_R_IN)
			close(prev->fds[0]);
}

int	ft_is_r_out(t_lstcmds *prev)
{
	if (prev)
		if (prev->token == TOKEN_R_D_OUT || prev->token == TOKEN_R_OUT)
			return (1);
	return (0);
}
