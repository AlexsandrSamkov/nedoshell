/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:07:50 by weambros          #+#    #+#             */
/*   Updated: 2021/04/14 22:09:41 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_spec(t_spec_chr *spec)
{
	if (!spec->quote && !spec->quotes && !spec->slash)
		return (0);
	return (1);
}

int	ft_switch_quotes(t_spec_chr *spec, char c)
{
	if (spec->quote == 1 && !spec->slash && c == '\'' && spec->quotes == 0)
	{
		spec->quote = 0;
		return (1);
	}
	if (spec->quote == 0 && !spec->slash && c == '\'' && spec->quotes == 0)
	{
		spec->quote = 1;
		return (1);
	}
	if (spec->quotes == 1 && !spec->slash && c == '\"' && spec->quote == 0)
	{
		spec->quotes = 0;
		return (1);
	}
	if (spec->quotes == 0 && !spec->slash && c == '\"' && spec->quote == 0)
	{
		spec->quotes = 1;
		return (1);
	}
	return (0);
}

int	ft_switch_slash(t_spec_chr *spec, char c)
{
	if (spec->slash == 1)
		return (spec->slash = 0);
	if (spec->quote)
		return (0);
	if (c == '\\')
		return (spec->slash = 1);
	else
		return (spec->slash = 0);
}

t_spec_chr	*ft_init_spec(void)
{
	t_spec_chr	*spec;

	spec = malloc(sizeof (t_spec_chr));
	if (!spec)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	spec->quote = 0;
	spec->quotes = 0;
	spec->slash = 0;
	return (spec);
}

int	ft_count_args_spec(char *s)
{
	int			count;
	int			i;
	t_spec_chr	*spec;

	spec = ft_init_spec();
	i = 0;
	count = 0;
	while (s[i])
	{
		ft_switch_quotes(spec, s[i]);
		if ((s[i] == '\"' && !spec->quote && !spec->slash)
			|| (s[i] == '\'' && !spec->quotes && !spec->slash)
			|| (s[i] == '\\' && !spec->quotes && !spec->quote && !spec->slash))
			count++;
		ft_switch_slash(spec, s[i]);
		i++;
	}
	spec = ft_free(spec);
	return (count);
}
