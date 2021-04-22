/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:39:43 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/20 14:43:07 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	excute_key(t_buttons keys[19], t_cmdline *l)
{
	int	i;

	i = -1;
	while (++i < 19)
		if (l->key == keys[i].key)
			keys[i].f(l);
}

char	*get_element_by_index(int index, t_data *list)
{
	t_data	*tmp;
	int		i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		if (i == index)
			return (tmp->data);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

void	top_k(t_cmdline *l)
{
	t_history	*h;
	int			i;
	char		*data;

	h = NULL;
	h = save_hist(&h);
	if (l->h_p >= h->count - 1)
		return ;
	l->h_p++;
	if (l->h_p == 0)
	{
		if (h->tmp)
			free(h->tmp);
		h->tmp = ft_strdup(l->chars);
	}
	data = get_element_by_index(l->h_p, h->hist_list);
	ft_strcpy(l->chars, data);
	i = l->cur;
	l->len = ft_strlen(data);
	l->cur = l->len;
}

void	bottom_k(t_cmdline *l)
{
	t_history	*h;
	int			i;
	char		*data;

	h = NULL;
	h = save_hist(&h);
	if (l->h_p <= -1)
		return ;
	l->h_p--;
	i = l->cur;
	if (l->h_p == -1)
	{
		ft_strcpy(l->chars, h->tmp);
		l->len = ft_strlen(h->tmp);
		free(h->tmp);
		h->tmp = NULL;
	}
	else
	{
		data = get_element_by_index(l->h_p, h->hist_list);
		ft_strcpy(l->chars, data);
		l->len = ft_strlen(data);
	}
	l->cur = l->len;
}

void	print_cmdline(t_cmdline *l)
{
	t_kursor	p;
	int			i;

	i = -1;
	init_cur(l);
	ft_putstr_fd(tgoto(CM, l->init_p->c - 1, l->init_p->r - 1), 1);
	ft_putstr_fd(CD, 1);
	show_prompt(l);
	while (++i < l->len)
	{
		if (i == l->cur)
			swap_p(&p, l->cur_p, 1);
		if (i == (l->cur - l->s_sp) && l->is_s)
			ft_putstr_fd(SO, 1);
		if (i == l->cur && l->is_s)
			ft_putstr_fd(SE, 1);
		if (l->chars[i] != '\n')
			ft_putchar_fd(l->chars[i], 1);
		plus(l->cur_p, l, &p, i);
	}
	if (l->cur != l->len)
		swap_p(&p, l->cur_p, 0);
	ft_putstr_fd(tgoto(CM, l->cur_p->c, l->cur_p->r), 1);
	ft_putstr_fd(SE, 1);
}
