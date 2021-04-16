/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:36:44 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 06:23:53 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_get_path(t_lstenv *env)
{
	char	**res;
	char	*value;

	value = 0;
	while (env)
	{
		if (!ft_strncmp("PATH", env->key, 5))
		{
			value = env->value;
			break ;
		}
		env = env->next;
	}
	if (!value)
		return (0);
	res = ft_split(value, ':');
	if (!res)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	return (res);
}

int	ft_free_bin(char **save_bin, char **bin, char *check, int ret)
{
	*save_bin = ft_free(*save_bin);
	*bin = ft_free(*bin);
	*bin = check;
	return (ret);
}

void	ft_my_bin(t_lstcmds *cmds)
{
	t_lstenv	*envs;

	ft_env(&envs, 0, GET_ENV);
	if (!ft_strncmp(cmds->args[0], "unset", 6)
		|| !ft_strncmp(cmds->args[0], "UNSET", 6))
		ft_errno(ft_unset(cmds->args), SET);
	if (!ft_strncmp(cmds->args[0], "env", 4)
		|| ft_strncmp(cmds->args[0], "ENV", 4))
		ft_errno(ft_export(cmds->args), SET);
	if (!ft_strncmp(cmds->args[0], "cd", 3)
		|| !ft_strncmp(cmds->args[0], "CD", 3))
		ft_errno(ft_cd(cmds->args), SET);
	if (!ft_strncmp(cmds->args[0], "exit", 5)
		|| !ft_strncmp(cmds->args[0], "EXIT", 5))
		ft_exit();
}

int	ft_check_bin(char *s)
{
	struct stat	sb;

	if (!s)
		return (ft_return_and_free(&sb, 0));
	if (stat(s, &sb) == -1)
		return (0);
	if (S_IXUSR & sb.st_mode)
		return (1);
	else if (S_IFREG == (sb.st_mode & S_IFMT))
		return (ERR_NO_PERM);
	return (0);
}

char	*ft_strdup_token(char *s, int start, int end)
{
	int		len;
	int		i;
	char	*res;

	res = 0;
	i = 0;
	if (!s)
		return (0);
	len = end - start + 1;
	if (start == end)
		len = 1;
	res = (char *)malloc(len + 1);
	if (!res)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	while (s[start] && start <= end)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}