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

char	*ft_lstenv_del_key(t_lstenv **env, char *key)
{
	t_lstenv	*begin;
	t_lstenv	*tmp;
	t_lstenv	*del;

	begin = *env;
	tmp = 0;
	if (!ft_strncmp(begin->key, key, ft_strlen(begin->key) + 1))
	{
		ft_lstenv_free(env);
		return (0);
	}
	while (begin)
	{
		if (!ft_strncmp(begin->key, key, ft_strlen(begin->key) + 1))
		{
			del = begin;
			tmp->next = begin->next;
			ft_lstenv_free(&del);
			return (0);
		}
		tmp = begin;
		begin = begin->next;
	}
	return (key);
}

int	ft_is_env_key(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (ft_isdigit(key[i]) || ft_isalpha(key[i]) || key[i] == '_')
			i++;
		else
			return (0);
	}		
	return (1);
}

int	ft_is_export(char *s)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	if (!(ft_isalpha(s[i]) ||  s[i] == '_'))
		return (-1);
	while (s[i])
	{
		if (s[i] == '=')
		{
			equal = 1;
			i++;
			break ;
		}
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_' && s[i] !=' ')
			return (-1);
		i++;
	}
	if (equal == 0)
		return (0);
	if (s[0] == '=')
		return (-1);
	if (s[i] == '\0')
		return (2);
	return (1);
}

int	ft_export(char *args[])
{
	int		i;
	int		ret;
	int		check;
	char	*tmp;
	char	**env;

	ret = 0;
	i = 1;
	env = ft_get_env_mass();
	if (ft_count_mass(args) == 1)
	{
		i = 1;
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
		i = 0;
		while (env[i] && env[i][0])
		{
			ft_putstr_fd( "declare -x ", 1);
			ft_putstr_fd(env[i],1);
			ft_putstr_fd("\n",1);
			i++;
		}
		ft_free_mas(&env);
		return (0);
	}
	else
	{
		while (args[i])
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
			i++;
		}
		return (ret);
	}
}

char	*ft_del_env_to_str(char **s, int i)
{
	char	*value;
	char	*tmp;
	int		j;
	int		get_err;

	get_err = 0;
	j = i + 1;
	if (s[0][j] == '?')
		get_err = j++;
	else
		while (ft_isalpha(s[0][j]) || ft_isdigit(s[0][j]))
			j++;
	value = ft_strdup_to_index(*s, i + 1, j);
	tmp = value;
	if (get_err)
		value = ft_int_to_str(ft_errno(0, GET));
	else
		value = ft_env(0, value, GET);
	tmp = ft_free(tmp);
	tmp = *s;
	*s = ft_del_str_from_str_by_index(*s, i, j);
	tmp = ft_free(tmp);
	return (value);
}
