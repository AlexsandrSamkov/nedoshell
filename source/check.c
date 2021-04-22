/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:16:22 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 04:14:08 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_r_out2(t_lstcmds *cmds, int j, char ***args)
{
	t_lstcmds	*next;
	int			i;

	next = cmds->next;
	i = 1;
	while (next->args[i])
		args[0][j++] = next->args[i++];
	args[0][j] = 0;
	cmds->args = ft_free(cmds->args);
	cmds->args = args[0];
	args[0] = ft_get_mas(1);
	args[0][0] = next->args[0];
	args[0][1] = 0;
	next->args = ft_free(next->args);
	next->args = args[0];
}

void	ft_check_r_out(t_lstcmds *cmds)
{
	int			count;
	int			j;
	char		**args;
	t_lstcmds	*next;

	next = cmds->next;
	if ((cmds->token == TOKEN_R_D_OUT || cmds->token == TOKEN_R_OUT)
		&& next && next->args)
	{
		count = ft_count_mass(next->args);
		if (count == 0 || count == 1)
			return ;
		j = ft_count_mass(cmds->args);
		args = ft_get_mas(count - 1 + j);
		j = 0;
		while (cmds->args && cmds->args[j])
		{
			args[j] = cmds->args[j];
			j++;
		}
		ft_check_r_out2(cmds, j, &args);
	}
}

void	ft_is_error_syntax(t_lstcmds *cmds)
{
	t_lstcmds	*next;

	next = cmds->next;
	if (!cmds->args && cmds->token != TOKEN_R_OUT && cmds->token != TOKEN_R_IN
		&& cmds->token != TOKEN_R_D_OUT)
		cmds->error = ERR_SYNTAX_ER;
	if (next && (cmds->token == TOKEN_R_OUT || cmds->token == TOKEN_R_IN
			|| cmds->token == TOKEN_R_D_OUT) && !next->args)
		cmds->error = ERR_SYNTAX_ER;
	if (!next && !cmds->args && (cmds->token == TOKEN_R_OUT
			|| cmds->token == TOKEN_R_IN || cmds->token == TOKEN_R_D_OUT))
		cmds->error = ERR_SYNTAX_ER;
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
		ft_check_r_out(begin);
		ft_is_error_syntax(begin);
		if (begin->args && begin->args[0])
			ft_get_bin(begin, bins);
		begin = begin->next;
	}
	ft_free_mas(&bins);
	return (0);
}
