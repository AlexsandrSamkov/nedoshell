/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 06:39:45 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 06:54:15 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_error_syntax(t_lstcmds *cmds)
{
	t_lstcmds	*next;

	while (cmds)
	{
		next = cmds->prev;
		if (cmds->error == ERR_SYNTAX_ER)
		{
			ft_errno(127,SET);
			if (write(2, MSG_ERR_SYNTAX_ERR, ft_strlen(MSG_ERR_SYNTAX_ERR)) < 0)
				ft_exit_fatal(MSG_ERR_NO_WRITE);
			return (1);
		}
		cmds = cmds->next;
	}
	return (0);
}

int	ft_run_error_2(t_lstcmds *cmds)
{
	if (cmds->error == ERR_NO_PERM)
	{
		ft_put_error(cmds->args[0]);
		ft_put_error(MSG_ERR_NO_PERM_F);
		ft_errno(126, SET);
		return (1);
	}
	if (cmds->error == ERR_NO_FILE)
	{
		ft_put_error(cmds->args[0]);
		ft_put_error(MSG_ERR_NO_FILE);
		ft_errno(127, SET);
		return (1);
	}
	if (cmds->error == ERR_FILE_NAME_ARGS)
	{
		ft_put_error(MSG_ERR_FILE_NAME_ARGS);
		ft_errno(127, SET);
		return (1);
	}
	return (0);
}

int	ft_run_error(t_lstcmds *cmds)
{
	if (cmds->error == ERR_N0_COMMAND)
	{
		ft_put_error(MSG_ERR_N0_COMMAND);
		ft_put_error(cmds->args[0]);
		ft_put_error("\n");
		ft_errno(127, SET);
		return (1);
	}
	if (cmds->error == ERR_IS_DIRECT)
	{
		ft_put_error(cmds->args[0]);
		ft_put_error(MSG_ERR_IS_DIRECT);
		ft_errno(126, SET);
		return (1);
	}
	return (ft_run_error_2(cmds));
}
