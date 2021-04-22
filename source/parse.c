/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:53:38 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 06:43:54 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_run_or_and(t_lstcmds **cmd)
{
	t_lstcmds	*cmds;

	cmds = *cmd;
	ft_check(cmds);
	ft_run_command(cmds);
	ft_lstcmdsdel(&cmds);
	*cmd = cmds;
}

void	ft_parse(char *line)
{
	t_lstcmds	*cmds;
	char		*str_token;
	int			token;
	int			i;
	int			ret;

	ret = 0;
	token = -1;
	cmds = 0;
	i = 0;
	while (line[i])
	{
		ft_get_token(line, &i, &str_token, &token);
		ft_insert_env_to_args(&str_token);
		ft_lstcmdsadd_back(&cmds, \
		ft_lstcmdsnew(ft_get_args(str_token), token));
		if (token == TOKEN_BIN)
			ft_run_or_and(&cmds);
		str_token = ft_free(str_token);
	}
	if (cmds)
	{
		ft_check(cmds);
		ft_run_command(cmds);
	}
	ft_lstcmdsdel(&cmds);
}
