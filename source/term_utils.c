#include "../includes/minishell.h"

t_lstenv	*creat_env(char **env)
{
	int			i;
	int			co;
	char		*tmp;
	char		*name;
	t_lstenv	*my_env;

	i = 0;
	my_env = 0;
	while (env && env[i])
	{
		tmp = env[i];
		co = 0;
		while (tmp[co] != '=')
			co++;
		name = ft_strsub(tmp, 0, co);
		if (!(name))
			return (0);
		if (add_to_env(&my_env, name, tmp + co + 1))
			return (0);
		ft_memdel((void **)&name);
		i++;
	}
	return (my_env);
}

int	check_spechar(char c)
{
	return (c == '>' || c == '<' || c == '&');
}

void	ctl_d(t_cmdline *l)
{
	if (l->len == 0)
	{
		l->ctl_d = 1;
		l->res = 0;
	}
}
