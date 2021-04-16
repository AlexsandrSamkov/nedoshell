/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env_to_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:12:49 by weambros          #+#    #+#             */
/*   Updated: 2021/04/14 22:09:27 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_insert_env_to_args(char **s)
{
	int			i;
	char		*value;
	char		*tmp;
	t_spec_chr	*spec;

	spec = ft_init_spec();
	i = 0;
	while (s[0][i])
	{
		ft_switch_quotes(&spec->quote, &spec->quotes, spec->slash, s[0][i]);
		if (s[0][i] == '$' && !spec->quote && !spec->slash)
		{
			value = ft_del_env_to_str(s, i);
			if (value)
			{
				tmp = *s;
				*s = ft_strjoin_index(*s, value, &i);
				tmp = ft_free(tmp);
				value = ft_free(value);
			}
			continue ;
		}
		ft_switch_slash(spec, s[0][i++]);
	}
	spec = ft_free(spec);
}
