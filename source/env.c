/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:53:24 by weambros          #+#    #+#             */
/*   Updated: 2021/04/15 02:03:14 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_env(t_lstenv **init, char *res, char parm)
{
	static t_lstenv	*env;
	t_lstenv		*begin;

	if (parm == INIT)
	{
		env = *init;
		return (0);
	}
	if (parm == GET_ENV)
		*init = env;
	if (parm == GET)
		return (ft_lst_get_env(env, res));
	if (parm == UNSET)
		return (ft_lstenv_del_key(&env, res));
	begin = env;
	if (parm == SET)
		ft_env_set(env, res);
	if (parm == ALL)
	{
		ft_env_put_all(env);
		exit(0);
	}
	return (0);
}

int	ft_unset(char **args)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!ft_is_env_key(args[i]))
		{
			ft_put_error(MSG_ERR_UNSET);
			ft_put_error(args[i]);
			ft_put_error(MSG_ERR_NOT_VALID_ID);
			ft_put_error("\n");
			ret = 1;
			break ;
		}
		else
			ft_env(0, args[i], UNSET);
		i++;
	}
	return (ret);
}

t_lstenv	*ft_get_lstenv(char **env)
{
	int			i;
	char		*key;
	char		*value;
	t_lstenv	*lstenv;
	t_lstenv	*new;

	i = 0;
	lstenv = 0;
	while (env[i])
	{
		ft_get_env_key_value(env[i], &key, &value);
		new = ft_lstenv_new(key, value);
		ft_lstenv_add_back(&lstenv, new);
		i++;
	}
	return (lstenv);
}

char 	**ft_get_env_mass_value(t_lstenv *env, char **res)
{
	char	*str;
	char	*tmp;
	int		i;

	str = 0;
	tmp = 0;
	i = 0;
	while (env)
	{
		str = ft_strjoin(env->key, "=");
		if (!str)
			ft_exit_fatal(MSG_ERR_NO_MALLOC);
		tmp = str;
		str = ft_strjoin(str, env->value);
		if (!str)
			ft_exit_fatal(MSG_ERR_NO_MALLOC);
		tmp = ft_free(tmp);
		res[i++] = str;
		env = env->next;
	}
	res[i] = 0;
	return (res);
}		

char	**ft_get_env_mass(t_lstenv *env)
{
	int			count;
	char		**res;
	t_lstenv	*begin;

	count = 0;
	begin = env;
	while (begin)
	{
		count++;
		begin = begin->next;
	}
	res = ft_get_mas(count);
	res = ft_get_env_mass_value(env, res);
	return (res);
}
