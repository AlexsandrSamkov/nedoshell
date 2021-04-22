/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 03:35:15 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 06:08:27 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

int	update_oldpwd(void)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	ft_env(0, oldpwd, SET);
	oldpwd = ft_free(oldpwd);
	return (SUCCESS);
}

int	go_to_path(int option)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd();
		env_path = ft_env(0, "HOME", GET);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", STDERR);
		if (!env_path)
			return (ERROR);
	}
	else if (option == 1)
	{
		env_path = ft_env(0, "HOME", GET);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR);
		if (!env_path)
			return (ERROR);
		update_oldpwd();
	}
	ret = chdir(env_path);
	env_path = ft_free(env_path);
	return (ret);
}

int	ft_cd(char **args)
{
	int	cd_ret;

	if (!args[1])
		return (go_to_path(0));
	if (!ft_strncmp(args[1], "-", 1) && ft_strlen((args[1])) == 1)
		cd_ret = go_to_path(1);
	else
	{
		update_oldpwd();
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}
