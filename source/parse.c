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

char *ft_get_cmds_line(char *s, int *i)
{
	t_spec_chr *spec;
	char *res;
	spec = ft_init_spec();
	while (s[*i])
	{
		ft_switch_quotes(spec,s[*i]);
		if (ft_check_spec(spec) && s[*i] == ';')
		{
			s[*i] = '\0';
			res = ft_strdup(s);
			if (!res)
				ft_exit_fatal(MSG_ERR_NO_MALLOC);
			(*i)++;
			return (res);
		}
		(*i)++;
	}
	res = ft_strdup(s);
	if (!res)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	return (res);
}


void	ft_parse(char *line)
{
	t_lstcmds	*cmds;
	char 		*cmds_line;
	char		*str_token;
	int			token;
	int			i;
	int j = 0;
	token = -1;
	cmds = 0;
	i = 0;
	cmds_line = 0;
	while(line[j])
	{
		cmds_line = ft_get_cmds_line(line, &j);
		ft_insert_env_to_args(&cmds_line);
		while (cmds_line[i])
		{
			ft_get_token(cmds_line, &i, &str_token, &token);

			ft_lstcmdsadd_back(&cmds, \
            ft_lstcmdsnew(ft_get_args(str_token), token));
			str_token = ft_free(str_token);
			if (cmds)
			{
				ft_check(cmds);
				ft_run_command(cmds);
			}
			ft_lstcmdsdel(&cmds);
			gl_pid = 0;
		}
		cmds_line = ft_free(cmds_line);
	}

}
