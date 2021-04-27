/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:57:54 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/20 16:25:28 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cur(t_cmdline *l)
{
	int	pr;
	int	len;

	len = ft_strlen(l->prompt);
	pr = (ft_strlen(l->prompt) + 5) / (l->w.ws_col);
	if (l->init_p->r == l->w.ws_row)
		l->init_p->r -= pr;
	l->cur_p->r = l->init_p->r - 1 + (pr);
	l->cur_p->c = l->init_p->c - 18 + ((len + 5) % (l->w.ws_col));
}

void	swap_p(t_kursor *p1, t_kursor *p2, int a)
{
	if (a)
	{
		p1->c = p2->c;
		p1->r = p2->r;
	}
	else
	{
		p2->c = p1->c;
		p2->r = p1->r;
	}
}

void	plus(t_kursor *p, t_cmdline *l, t_kursor *p1, int i)
{
	if (p->c == l->w.ws_col - 1 || l->chars[i] == '\n')
	{
		p->c = 0;
		if (p->r == (l->w.ws_row - 1))
		{
			l->init_p->r--;
			p1->r--;
			ft_putstr_fd((tgetstr("do", NULL)), 1);
		}
		else
			p->r++;
		ft_putstr_fd(tgoto((tgetstr("cm", NULL)), p->c, p->r), 1);
	}
	else
		p->c++;
}

void	free_out(t_cmdline *l)
{
	if (l)
	{
		ft_bzero(l->chars, BUFF_SIZE);
		if (l->cur_p)
			free(l->cur_p);
		if (l->init_p)
			free(l->init_p);
		free(l);
		keep_l(NULL, 0);
	}
	ft_putchar('\n');
}

void	go_to_the_end(t_cmdline *l)
{
	l->cur = l->len;
	print_cmdline(l);
}
