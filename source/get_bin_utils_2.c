/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 06:23:33 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 06:09:00 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_run_2(struct stat sb, t_lstcmds *cmds)
{
	if (S_IFREG == (sb.st_mode & S_IFMT))
	{
		if (!(S_IXUSR & sb.st_mode))
		{
			cmds->error = ERR_NO_PERM;
			return (0);
		}
		if (S_IFDIR == (sb.st_mode & S_IFMT))
		{
			cmds->error = ERR_IS_DIRECT;
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	ft_check_run(char *s, t_lstcmds *cmds)
{
	struct stat	sb;
	int			ret;

	if (!s)
		return (0);
	if (!(ft_strncmp(s, ".", 2)))
	{
		cmds->error = ERR_FILE_NAME_ARGS;
		return (0);
	}
	if (stat(s, &sb) == -1)
	{
		cmds->error = ERR_NO_FILE;
		return (0);
	}
	if (!ft_strncmp("./", s, 3))
	{
		cmds->error = ERR_IS_DIRECT;
		return (0);
	}
	ret = ft_check_run_2(sb, cmds);
	if (ret != -1)
		return (ret);
	cmds->error = ERR_IS_DIRECT;
	return (0);
}

int	ft_get_bin(t_lstcmds *cmds, char **bins)
{
	t_lstcmds	*prev;

	prev = cmds->prev;
	if (prev)
		if (prev->token == TOKEN_R_D_OUT || prev->token == TOKEN_R_OUT
			|| prev->token == TOKEN_R_IN)
			return (1);
	if (ft_is_no_fork(cmds->args[0]))
		return (cmds->error = 2);
	if (!ft_strncmp("env", cmds->args[0], 4)
		&& ft_strlen(cmds->args[0]) == 3)
		return (cmds->error = 3);
	if (!ft_strncmp("pwd", cmds->args[0], 4)
		&& ft_strlen(cmds->args[0]) == 3)
		return (cmds->error = 3);
	if (!ft_strncmp("echo", cmds->args[0], 5)
		&& ft_strlen(cmds->args[0]) == 4)
		return (cmds->error = 3);
	if (!ft_strncmp("./", cmds->args[0], 3)
		|| !ft_strncmp(".", cmds->args[0], 2)
		|| ft_strchr(cmds->args[0], '/'))
		return (ft_check_run(cmds->args[0], cmds));
	cmds->error = ft_check_bins(&cmds->args[0], bins);
	return (0);
}

int	ft_check_bins(char **bin, char **bins)
{
	int		i;
	char	*check;
	char	*save_bin;
	int		ret;

	if (!bins)
		return (ERR_N0_COMMAND);
	check = ft_strjoin("/", *bin);
	save_bin = check;
	ft_check_str_fatal(check);
	i = 0;
	while (bins[i])
	{
		check = ft_strjoin(bins[i], save_bin);
		ft_check_str_fatal(check);
		ret = ft_check_bin(check);
		if (!ret)
			check = ft_free(check);
		else
			return (ft_free_bin(&save_bin, bin, check, ret));
		check = save_bin;
		i++;
	}
	save_bin = ft_free(save_bin);
	return (ERR_N0_COMMAND);
}
