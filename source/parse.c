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

char	*ft_get_cmds_line(char *s, int *i)
{
	t_spec_chr	*spec;
	char		*res;

	spec = ft_init_spec();
	while (s[*i])
	{
		ft_switch_quotes(spec, s[*i]);
		if (ft_check_spec(spec) && s[*i] == ';')
		{
			s[*i] = '\0';
			res = ft_strdup(s);
			if (!res)
				ft_exit_fatal(MSG_ERR_NO_MALLOC);
			(*i)++;
			spec = ft_free(spec);
			return (res);
		}
		(*i)++;
	}
	spec = ft_free(spec);
	res = ft_strdup(s);
	if (!res)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	return (res);
}

t_parse	*ft_init_parse(void)
{
	t_parse	*p;

	p = malloc(sizeof(t_parse));
	if (!p)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	p->j = 0;
	p->token = -1;
	p->cmds = 0;
	p->i = 0;
	p->cmds_line = 0;
	return (p);
}

void	ft_parse(char *line)
{
	t_parse	*p;

	p = ft_init_parse();
	while (line[p->j])
	{
		p->cmds_line = ft_get_cmds_line(line, &p->j);
		ft_insert_env_to_args(&p->cmds_line);
		while (p->cmds_line[p->i])
		{
			ft_get_token(p->cmds_line, &p->i, &p->str_token, &p->token);
			ft_lstcmdsadd_back(&p->cmds, \
			ft_lstcmdsnew(ft_get_args(p->str_token), p->token));
			p->str_token = ft_free(p->str_token);
			g_pid = 0;
		}
		ft_check(p->cmds);
		ft_run_command(p->cmds);
		ft_lstcmdsdel(&p->cmds);
		p->cmds_line = ft_free(p->cmds_line);
	}
	p = ft_free(p);
}
