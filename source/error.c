/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 19:01:59 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 06:08:48 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit_fatal(char *s)
{
	write(2, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

void	ft_put_error(char *s)
{
	int	len;

	len = (int)ft_strlen(s);
	if (!s || !len)
		return ;
	if (write(2, s, ft_strlen(s)) < 0)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
}

int	ft_errno(int n, char f)
{
	static int	err;

	if (f == SET)
		err = n;
	return (err);
}

void	ft_check_str_fatal(char *str)
{
	if (!str)
		ft_put_error(MSG_ERR_NO_MALLOC);
}
