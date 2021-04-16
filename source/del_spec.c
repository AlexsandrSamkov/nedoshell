/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_spec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:36:07 by weambros          #+#    #+#             */
/*   Updated: 2021/04/15 04:35:30 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_if_del_spec(char *s, int j, t_spec_chr *spec)
{
	int	ret;

	ret = !((s[j] == '\"' && !spec->quote && !spec->slash) \
	|| (s[j] == '\'' && !spec->quotes && !spec->slash) \
	|| (s[j] == '\\' && !spec->quote && !spec->slash));
	return (ret);
}

void	ft_del_spec(char **s)
{
	int			i;
	int			j;
	char		*res;
	t_spec_chr	*spec;

	spec = ft_init_spec();
	i = 0;
	j = 0;
	res = malloc(ft_strlen(*s) - ft_count_args_spec(*s) + 1);
	if (!res)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	while (s[0][j])
	{
		ft_switch_quotes(&spec->quote, &spec->quotes, spec->slash, s[0][j]);
		if (ft_if_del_spec(s[0], j, spec))
			res[i++] = s[0][j];
		ft_switch_slash(spec, s[0][j++]);
	}
	res[i] = '\0';
	*s = ft_free(*s);
	*s = res;
	spec = ft_free(spec);
}
