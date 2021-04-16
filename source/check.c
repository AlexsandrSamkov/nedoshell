/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:16:22 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 05:55:05 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_swap_in_token_args(t_lstcmds *cmds, t_lstcmds *next)
{
	int		i;
	char	**tmp;

	i = 1;
	tmp = next->args;
	cmds->args = ft_get_mas(ft_count_mass(tmp) - 1);
	while (tmp[i])
	{
		cmds->args[i - 1] = tmp[i];
		i++;
	}
	cmds->args[i - 1] = 0;
	next->args = ft_get_mas(1);
	next->args[0] = tmp[0];
	next->args[1] = 0;
}

void	ft_is_error_syntax(t_lstcmds *cmds)
{
	t_lstcmds	*prev;
	t_lstcmds	*next;

	prev = cmds->prev;
	next = cmds->next;
	if (!cmds->args
		&& (cmds->token == TOKEN_R_D_OUT || cmds->token == TOKEN_R_OUT)
		&& ((prev && prev->token == 1) || !prev) && next && next->args)
		ft_swap_in_token_args(cmds, next);
	else if (!cmds->args)
		cmds->error = ERR_SYNTAX_ER;
}

int	ft_cmds_swap_r_out(t_lstcmds **cmds)
{
	char		**tmp;
	t_lstcmds	*swap;
	t_lstcmds	*cmds_temp;

	cmds_temp = *cmds;
	*cmds = cmds_temp->next;
	swap = *cmds;
	cmds_temp = *cmds;
	while (cmds_temp)
	{
		if (cmds_temp ->token
			!= TOKEN_R_D_OUT && cmds_temp->token != TOKEN_R_OUT)
			break ;
		cmds_temp = cmds_temp->next;
		*cmds = cmds_temp;
	}
	if (!*cmds)
		return (1);
	tmp = cmds_temp->args;
	cmds_temp->args = swap->args;
	swap->args = tmp;
	return (0);
}

void	ft_check_r_out(t_lstcmds *cmds)
{
	t_lstcmds	*next;

	while (cmds)
	{
		next = cmds->next;
		if (next && (cmds->token == TOKEN_R_D_OUT || cmds->token == TOKEN_R_OUT)
			&& (next->token == TOKEN_R_D_OUT || next->token == TOKEN_R_OUT))
			if (ft_cmds_swap_r_out(&cmds))
				return ;
		cmds = cmds->next;
	}
}

int	ft_check(t_lstcmds *cmds)
{
	char		**bins;
	t_lstcmds	*begin;
	t_lstenv	*env;

	ft_env(&env, 0, GET_ENV);
	begin = cmds;
	bins = ft_get_path(env);
	while (begin)
	{
		ft_is_error_syntax(begin);
		if (begin->args && begin->args[0])
			ft_get_bin(begin, bins);
		begin = begin->next;
	}
	ft_check_r_out(cmds);
	ft_free_mas(&bins);
	return (0);
}
