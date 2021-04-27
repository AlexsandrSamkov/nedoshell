/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 01:29:40 by weambros          #+#    #+#             */
/*   Updated: 2021/04/24 19:04:22 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_export(char *s)
{
	int	i;
	int	equal;

	i = -1;
	equal = 0;
	if (!(ft_isalpha(s[0]) || s[0] != '_'))
		return (-1);
	while (s[++i])
	{
		if (s[i] == '=')
		{
			equal = 1;
			i++;
			break ;
		}
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_' && s[i] !=' ')
			return (-1);
	}
	if (equal == 0)
		return (0);
	if (s[0] == '=')
		return (-1);
	if (s[i] == '\0')
		return (2);
	return (1);
}

char	**ft_exprort_sort_mass(void)
{
	char	**env;
	int		ret;
	char	*tmp;
	int		i;

	i = 1;
	env = ft_get_env_mass();
	while (env[i])
	{
		ret = 0;
		while (ret <= ft_count_mass(env) - i - 1)
		{
			if (env[ret + 1][0] < env[ret][0])
			{
				tmp = env[ret];
				env[ret] = env[ret + 1];
				env[ret + 1] = tmp;
			}
			ret++;
		}
		i++;
	}
	return (env);
}

int	ft_export_print(void)
{
	int		i;
	char	**env;

	env = ft_exprort_sort_mass();
	i = 0;
	while (env[i] && env[i][0])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	ft_free_mas(&env);
	return (0);
}

int	ft_export(char *args[])
{
	int		i;
	int		ret;
	int		check;

	ret = 0;
	i = 0;
	if (ft_count_mass(args) == 1)
		return (ft_export_print());
	else
	{
		while (args[++i])
		{
			check = ft_is_export(args[i]);
			if (check < 0)
			{
				ret = 1;
				ft_put_error("export: `");
				ft_put_error(args[i]);
				ft_put_error("\': not a valid identifier\n");
			}
			if (check >= 0)
				ft_env(0, args[i], SET);
		}
		return (ret);
	}
}
