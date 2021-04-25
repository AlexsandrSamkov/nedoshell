/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 03:40:32 by weambros          #+#    #+#             */
/*   Updated: 2021/04/25 15:31:17 by sjennett         ###   ########.fr       */
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

		while (argv[i] && !ft_strncmp(argv[i], "-n", 3) && ft_strlen((argv[i]))
		== 2)
		{
			flag = 1;
			i++;
		}
		while (argv[i])
		{
			if (write(1,argv[i], ft_strlen(argv[i])) < 0)
				ft_exit_fatal(MSG_ERR_NO_WRITE);
			if (argv[i + 1] && argv[i][0] != '\0')
				if ((write(1, " ", 1)) < 0)
					ft_exit_fatal(MSG_ERR_NO_WRITE);
			i++;
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}

int ft_atol(char *s, unsigned long long *check)
{
	long long n;
	int i;
	int sign;
	*check = 0;
	sign = 0;
	i = -1;
	if (s[0] == '-')
		sign = (int)s[++i] - 44;
	while (s[++i])
	{
		if (i > 19 + sign || !ft_isdigit(s[i]))
			return (0);
		*check = *check * 10 + s[i] - 48;
	}
	if ((sign && *check > (unsigned long long)LLONG_MAX + 1) || (!sign && *check > LLONG_MAX))
		return (0);
	n = (long long) *check;
	if (sign)
		n *= -1;
	*check = (unsigned long long) n;
	return (1);
}

int	ft_exit(char *args[])
{
	unsigned long long res;

	res = 0;
	if (!args || !args[1])
		exit(ft_errno(0, GET));
	ft_putstr_fd("exit ",2);
	if (!ft_atol(args[1], &res))
	{
		ft_putstr_fd(args[1],2);
		ft_putstr_fd(" : numeric argument required",2);
		exit(255);
	}
	if (!args[2])
		exit(res % 256);
	ft_putstr_fd(" : too many arguments\n",2);
	ft_errno(1, SET);
	return(1);
}
