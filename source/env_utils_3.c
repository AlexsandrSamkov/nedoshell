#include "../includes/minishell.h"

void	ft_env_put_all(t_lstenv *env)
{
	while (env)
	{
		if (env->value)
		{
			if (write(1, env->key, (int) ft_strlen(env->key)) < 0)
				ft_exit_fatal(MSG_ERR_NO_MALLOC);
			if (write(1, "=", 1) < 0)
				ft_exit_fatal(MSG_ERR_NO_MALLOC);
			if (write(1, env->value, (int) ft_strlen(env->value)) < 0)
				ft_exit_fatal(MSG_ERR_NO_MALLOC);
			if (write(1, "\n", 1) < 0)
				ft_exit_fatal(MSG_ERR_NO_MALLOC);
		}
		env = env->next;
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
	if (ft_isdigit(key[i]))
		return (0);
	while (key[i])
	{
		if (ft_isdigit(key[i]) || ft_isalpha(key[i]) || key[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}
