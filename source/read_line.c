/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:39:58 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/16 20:18:53 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_lstenv *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(name, env->key))
			return (env->value);
		env = env->next;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	else
		return (0);
}

char	*read_line2(t_cmdline *l)
{
	char	*result;

	if (l->ctl_d)
		result = NULL;
	else if (l->ctl_c)
		result = ft_strdup("\n");
	else
		result = ft_strdup(l->chars);
	free_out(l);
	return (result);
}

char	*read_line(char *prompt)
{
	t_cmdline	*l;

	init_term();
	l = init_cmdline(prompt);
	if ((l) == NULL)
		return (0);
	l->chars[0] = 0;
	keep_l(l, 0);
	while (l->res)
	{
		read_key(l);
		match_key(l);
		print_cmdline(l);
		if (l->is_s == 0)
			l->s_sp = 0;
		l->is_s = 0;
	}
	go_to_the_end(l);
	default_term_mode();
	return (read_line2(l));
}

void	init_term(void)
{
	char			*termtype;
	int				success;
	struct termios	tattr;

	termtype = getenv("TERM");
	if (termtype == 0)
		ft_putstr_fd("Specify a terminal type'.\n", 2);
	success = tgetent(0, termtype);
	if (success < 0)
		ft_putstr_fd("Could not access the termcap data base.\n", 2);
	if (success == 0)
		ft_putstr_fd("Terminal type  is not defined.\n", 2);
	if (termtype == 0 || success <= 0)
		exit(0);
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_oflag &= ~(OPOST);
	tcsetattr(STDIN_FILENO, TCSANOW, &tattr);
}
