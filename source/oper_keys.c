/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:39:49 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/22 08:41:46 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmdline	*keep_l(t_cmdline *l, int cmd)
{
	static t_cmdline	*tmp;

	if (cmd)
		return (tmp);
	tmp = l;
	return (l);
}

void	read_key(t_cmdline *l)
{
	int		res;
	char	buff[READ_SIZE];
	int		i;

	res = read(0, buff, READ_SIZE);
	ft_bzero(buff + res, 3);
	i = -1;
	while (buff[++i] && ft_isprint(buff[i]))
	{
		l->key = buff[i];
		add_at(l);
	}
	l->key = 0;
	if (res <= 4)
		l->key = *(int *)buff;
}

void	sheft(t_cmdline *l)
{
	int	i;

	i = l->len;
	while (i >= l->cur)
	{
		l->chars[i] = l->chars[i - 1];
		i--;
	}
	l->chars[l->cur] = (int)l->key;
}

void	add_at(t_cmdline *l)
{
	if (l->cur == l->len)
		l->chars[l->cur] = (int)l->key;
	else
	{
		sheft(l);
	}
	l->len++;
	l->cur++;
	l->chars[l->len] = '\0';
}

void	match_key(t_cmdline *l)
{
	static t_buttons	keys[19] = {
		{RIGHT_K, &right_kursor},
		{LEFT_K, &left_kursor},
		{BACK_K, &delete},
		{END_K, &end_k},
		{HOME_K, &home_k},
		{INTER_K, &return_k},
		{CTL_D, &ctl_d},
		{UP_K, &up_k},
		{DOWN_K, &down_k},
		{TOP_K, &top_k},
		{BOTTOM_K, &bottom_k},
	};

	excute_key(keys, l);
}
