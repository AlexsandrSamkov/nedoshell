/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 01:10:58 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 06:12:10 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lstenv	*ft_lstenv_new(char *key, char *value)
{
	t_lstenv	*new;

	new = malloc(sizeof (t_lstenv));
	if (!new)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	new->key = key;
	new->value = value;
	new->next = 0;
	return (new);
}

t_lstenv	*ft_lstenv_last(t_lstenv *lstenv)
{
	if (!lstenv)
		return (0);
	while (lstenv->next)
		lstenv = lstenv->next;
	return (lstenv);
}

void	ft_lstenv_add_back(t_lstenv **lstenv, t_lstenv *new)
{
	t_lstenv	*begin;

	begin = *lstenv;
	if (begin)
	{
		begin = ft_lstenv_last(begin);
		begin->next = new;
	}
	else
		*lstenv = new;
}

void	ft_lstenv_free(t_lstenv **del)
{
	t_lstenv	*tmp;

	tmp = *del;
	tmp->key = ft_free(tmp->key);
	tmp->value = ft_free(tmp->value);
	free(*del);
	*del = 0;
}

void	ft_lstenv_del_all(t_lstenv **lstenv)
{
	t_lstenv	*tmp;
	t_lstenv	*begin;

	begin = *lstenv;
	while (begin)
	{
		tmp = begin;
		begin = begin->next;
		ft_lstenv_free(&tmp);
	}
}
