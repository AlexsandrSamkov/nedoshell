/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:18:33 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 05:57:40 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_args_val(char *line, int start, int end)
{
	char	*res;

	res = ft_strdup_to_index(line, start, end);
	if (!res)
		ft_exit_fatal (MSG_ERR_NO_MALLOC);
	ft_del_spec(&res);
	return (res);
}

char	*ft_get_args_str(char *line, int *i)
{
	t_spec_chr	*spec;
	int			start;
	char		*res;

	res = 0;
	spec = ft_init_spec();
	start = *i;
	while (line[*i])
	{
		ft_switch_quotes(spec, line[*i]);
		if ((line[*i] == ' ' && !ft_check_spec(spec)) || !line[*i])
		{
			res = ft_get_args_val(line, start, *i);
			while (line[*i] == ' ')
				(*i)++;
			break ;
		}
		ft_switch_slash(spec, line[*i]);
		(*i)++;
	}
	if (!line[*i])
		res = ft_get_args_val(line, start, *i);
	ft_free(spec);
	return (res);
}

int	ft_args_count(char *line)
{
	int			count;
	int			i;
	t_spec_chr	*spec;

	spec = ft_init_spec();
	i = 0;
	count = 1;
	while (line[i])
	{
		ft_switch_quotes(spec, line[i]);
		if (!ft_check_spec(spec) && line[i] == ' ')
		{
			while (line[i] && line[i] == ' ')
				i++;
			if (!line[i])
				break ;
			count++;
			continue ;
		}
		ft_switch_slash(spec, line[i]);
		i++;
	}
	spec = ft_free(spec);
	return (count);
}

char	**ft_get_args(char *line)
{
	int		i;
	int		count;
	char	**args;
	int		j;

	j = 0;
	i = 0;
	if (!line || (line && line[0] == '\0'))
		return (0);
	count = ft_args_count(line);
	args = ft_get_mas(count);
	if (!args)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	while (j < count)
	{
		args[j] = ft_get_args_str(line, &i);
		if (!args[j])
			ft_exit_fatal(MSG_ERR_NO_MALLOC);
		j++;
	}
	args[j] = 0;
	return (args);
}
