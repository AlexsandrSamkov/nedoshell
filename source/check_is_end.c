/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:39:27 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/24 18:46:23 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valtok(char c)
{
	if (check_spechar(c) || c == '|')
		return (0);
	return (1);
}

static int	check_quotes(char *str, char q)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == q)
			return (i);
		i++;
	}
	return (0);
}

static int	after_pipe(char *str)
{
	int	i;

	i = 0;
	if (str[i])
	{
		while (check_space(str[i]))
			i++;
		if (str[i])
			return (0);
	}
	return (1);
}

int	check_errline2(char *str, int ret)
{
	if (check_spechar(*str))
	{
		ret = check_redirect(str);
		if ((ret) == 0)
			return (-1);
		str += ret;
	}
	else if (*str == '|')
	{
		ret = after_pipe(++str);
		if ((ret))
			return (ret);
	}
	else if (*str != '\\')
	{
		str++;
		if (*str == ' ')
		{
			str++;
			if (*str == '#')
				return (5);
		}
	}
	return (0);
}

int	check_errline(char *str)
{
	int	ret;

	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			ret = check_quotes(str, *str);
			if (ret == 0)
				return (2);
			str += ret + 1;
		}
		else
		{
			ret = check_errline2(str, ret);
			if (ret != 0)
				return (ret);
			else
				str++;
		}
	}
	return (0);
}
