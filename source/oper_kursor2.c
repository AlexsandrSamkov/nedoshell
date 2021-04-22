/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_kursor2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:34:42 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/16 20:05:53 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_environ(t_lstenv *lst)
{
	t_lstenv	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&(lst->key));
		ft_memdel((void **)&(lst->value));
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}

void	right_kursor(t_cmdline *l)
{
	if (l->cur >= l->len)
		return ;
	l->cur++;
}

void	left_kursor(t_cmdline *l)
{
	if (l->cur - l->b_p <= 0)
		return ;
	l->cur--;
}

void	delete(t_cmdline *l)
{
	int	i;

	if (l->cur - l->b_p <= 0)
		return ;
	i = l->cur - 1;
	while (i < l->len)
	{
		l->chars[i] = l->chars[i + 1];
		i++;
	}
	l->len--;
	l->cur--;
}
