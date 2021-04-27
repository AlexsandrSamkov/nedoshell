/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 19:38:06 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 06:08:42 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_lst_get_env(t_lstenv *env, char *s)
{
	char	*res;

	res = 0;
	while (env)
	{
		if (!ft_strncmp(s, env->key, ft_strlen(s))
			&& ft_strlen(env->key) == ft_strlen(s))
		{
			res = ft_strdup(env->value);
			if (!res)
				ft_exit_fatal(MSG_ERR_NO_MALLOC);
		}
		env = env->next;
	}
	return (res);
}

void	ft_get_env_key_value_2(char *env, char **key, char **value)
{
	char	*tmp;
	int		i;

	tmp = ft_strdup(env);
	if (!tmp)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	i = 0;
	while (tmp[i] != '=')
		i++;
	tmp[i] = '\0';
	*key = ft_strdup(tmp);
	if (!*key[0])
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	tmp += ++i;
	*value = ft_strdup(tmp);
	if (!value[0])
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	tmp -= i;
	tmp[i] = '=';
	free(tmp);
}

void	ft_get_env_key_value(char *env, char **key, char **value)
{
	if (!ft_strchr(env, '='))
	{
		*key = ft_strdup(env);
		if (!(*key))
			ft_exit_fatal(MSG_ERR_NO_MALLOC);
		*value = 0;
		return ;
	}
	ft_get_env_key_value_2(env, key, value);
}

int	ft_env_set_2(t_lstenv *env, t_lstenv *next, char *key, char *value)
{
	while (env->next)
	{
		next = env->next;
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
		{
			key = ft_free(key);
			ft_free(env->value);
			env->value = value;
			return (1);
		}
		if (next && !ft_strncmp(next->key, key, ft_strlen(key) + 1))
		{
			key = ft_free(key);
			ft_free(next->value);
			next->value = value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	ft_env_set(t_lstenv *env, char *set)
{
	char		*key;
	char		*value;
	t_lstenv	*new;
	t_lstenv	*next;

	next = 0;
	ft_get_env_key_value(set, &key, &value);
	if (ft_env_set_2(env, next, key, value))
		return ;
	new = ft_lstenv_new(key, value);
	if (!new)
		ft_exit_fatal(MSG_ERR_NO_MALLOC);
	while (env->next)
		env = env->next;
	env->next = new;
}
