/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:39:54 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/20 15:11:57 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

t_cmdline	*init_cmdline(char *pr)
{
	t_cmdline	*l;

	l = malloc_cmd();
	if (l == NULL || l->init_p == NULL || l->cur_p == NULL)
		return (NULL);
	ft_strcpy(l->prompt, pr);
	get_cur_pos(l->cur_p);
	get_cur_pos(l->init_p);
	show_prompt(l);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &(l->w));
	l->len = 0;
	l->b_p = 0;
	l->cur_p->c--;
	l->cur_p->r--;
	l->cur = 0;
	l->is_s = 0;
	l->s_sp = 0;
	l->res = 1337;
	l->h_p = -1;
	l->ctl_d = 0;
	l->ctl_c = 0;
	return (l);
}

t_cmdline	*malloc_cmd(void)
{
	t_cmdline	*l;

	l = (t_cmdline *)malloc(sizeof(t_cmdline));
	l->init_p = (t_kursor *)malloc(sizeof(t_kursor));
	l->cur_p = (t_kursor *)malloc(sizeof(t_kursor));
	return (l);
}

void	get_cur_pos(t_kursor *t)
{
	char	pos[20];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(pos, 20);
	i = read(0, pos, 20);
	pos[i] = 0;
	i = 2;
	t->r = ft_atoi(pos + i);
	while (ft_isdigit(pos[i]))
		i++;
	t->c = ft_atoi(pos + i + 1);
}
