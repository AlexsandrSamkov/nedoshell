/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_end2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:39:34 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/20 16:39:05 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	check_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	check_spacestr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!check_space(str[i++]))
			return (0);
	return (1);
}

int	check_allerr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_spechar(str[i]))
		{
			while (check_spechar(str[i]))
				i++;
			while (check_space(str[i]))
				i++;
			while (ft_isdigit(str[i]))
				i++;
			if (check_spechar(str[i]))
				return (ft_perror(0, "syntax error near unexpected token", -1));
		}
		i++;
	}
	return (check_errline(str));
}

int	check_aller(char *str)
{
	int	i;
	int	be;

	i = 0;
	if (str[0] == '|')
		return (ft_perror(0, "syntax error near unexpected token", -1));
	while (str[i])
	{
		if (str[i] == ';' || str[i] == '|')
		{
			be = i++;
			while (str[i] && check_space(str[i]))
				i++;
			if (str[i] == '|' || (str[i] == ';' && str[be] == '|'))
				return (ft_perror(0, "syntax error near unexpected token", -1));
		}
		else
			i++;
	}
	return (check_errline(str));
}

int	ft_perror(char *s, char *str, int ret)
{
	ft_putstr_fd("21sh: ", 2);
	if (s)
		ft_putstr_fd(s, 2);
	ft_putendl_fd(str, 2);
	return (ret);
}
