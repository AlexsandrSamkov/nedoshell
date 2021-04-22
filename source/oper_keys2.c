/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_keys2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:40:03 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/16 21:23:59 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	down_k(t_cmdline *l)
{
	int	i;
	int	p;

	i = l->cur;
	p = 0;
	while (--i >= 0 && l->chars[i] != '\n')
		p++;
	i = l->cur;
	while (i < l->len && l->chars[i] != '\n')
		i++;
	if (i == l->len)
		return ;
	p += i++;
	p++;
	while (i < l->len && l->chars[i] != '\n')
		i++;
	if (i < p)
		l->cur = i;
	else
		l->cur = p;
}

void	up_k(t_cmdline *l)
{
	int	i;
	int	p;

	i = l->cur;
	p = 0;
	while (--i >= 0 && l->chars[i] != '\n')
		p++;
	if (--i <= 0)
		return ;
	while (i >= 0 && l->chars[i] != '\n')
		i--;
	p += i++;
	p++;
	while (l->chars[i] != '\n')
		i++;
	if (i < p)
		l->cur = i;
	else
		l->cur = p;
}

void	end_k(t_cmdline *l)
{
	l->cur = l->len;
}

void	home_k(t_cmdline *l)
{
	l->cur = l->b_p;
}

void	return_k(t_cmdline *l)
{
	l->res = 0;
}
