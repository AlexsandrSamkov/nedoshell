/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_promt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:39:58 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/24 18:48:44 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_to_env(t_lstenv **env, char *name, char *value)
{
	t_lstenv	*tmp;

	if (*env)
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem_env(name, value);
		if (!(tmp->next))
			return (1);
	}
	else
	{
		*env = elem_env(name, value);
		if (!(*env))
			return (1);
	}
	return (0);
}

char	*prompt(t_lstenv *env)
{
	char	*tp;
	char	*ret;

	tp = ft_getenv(env, "PWD");
	if (tp)
		tp = ft_strdup(tp);
	else
		tp = getcwd(0, 0);
	return (read_line("\x1b[31mWait CMD\U0001f408: \x1b[94m"));
	ret = read_line(tp);
	ft_memdel((void **)&tp);
	return (ret);
}

int	check_redirect(char *str)
{
	int		i;
	int		ret;
	char	*rd;

	i = 0;
	ret = 0;
	while (check_spechar(str[i]))
		i++;
	rd = ft_strsub(str, 0, i);
	if (!(rd))
		return (0);
	while (check_space(str[i]))
		i++;
	if (str[i] && check_valtok(str[i]))
	{
		if (!ft_strcmp(rd, ">") || !ft_strcmp(rd, "<"))
			ret = 1;
		if (!ft_strcmp(rd, ">>") || !ft_strcmp(rd, "<<") || !ft_strcmp(rd, "<&") \
		|| !ft_strcmp(rd, "&>") || !ft_strcmp(rd, "&<") || !ft_strcmp(rd, ">&"))
			ret = 2;
	}
	ft_memdel((void **)&rd);
	if (!ret)
		ft_perror(0, " syntax error near unexpected token", 1);
	return (ret);
}
