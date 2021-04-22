/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 03:40:32 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 06:09:32 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = malloc(4096);
	if (!pwd)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	if (getcwd(pwd, 4096))
	{
		ft_putendl_fd(pwd, 1);
		pwd = ft_free(pwd);
		return (0);
	}
	else
	{
		pwd = ft_free(pwd);
		return (1);
	}
}

int	ft_echo(char **argv)
{
	int		i;
	int		flag;
	int		argc;

	i = 1;
	flag = 0;
	argc = ft_count_mass(argv);
	if (argc > 1)
	{
		if (!ft_strncmp(argv[i], "-n", 3) && ft_strlen((argv[i])) == 2)
			flag = 1;
		i++;
		while (argv[i])
		{
			ft_putendl_fd(argv[i], 1);
			if (argv[i + 1] && argv[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}

void	ft_exit(void)
{
	t_lstenv	*env;

	ft_env(&env, 0, GET_ENV);
	ft_lstenv_del_all(&env);
	exit(0);
}
