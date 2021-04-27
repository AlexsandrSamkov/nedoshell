#include "../includes/minishell.h"

void	process(int sign_num)
{
	if (sign_num == SIGQUIT)
	{
		kill(g_pid, sign_num);
		if (g_fix_sigquit != 1)
			ft_putstr_fd("Quit: 3\n", 1);
		g_pid = 0;
	}
	else if (sign_num == SIGINT)
		ft_putchar_fd('\n', 1);
}

void	signal_manager(int sign_num)
{
	t_cmdline	*l;
	char		buf[2];

	if ((sign_num == SIGQUIT && g_pid != 0) \
		|| (sign_num == SIGINT && g_pid != 0))
		process(sign_num);
	else if (sign_num == SIGINT)
	{
		l = NULL;
		l = keep_l(l, 1);
		if (l != NULL)
		{
			l->res = 0;
			l->ctl_c = 1;
			buf[0] = -62;
			buf[1] = 0;
			ioctl(0, TIOCSTI, buf);
		}
		else
			ft_putchar('\n');
	}
}

void	ft_main_init(int *argc, char ***argv)
{
	(void)*argc;
	(void)*argv;
	ft_pid_mass(INIT, 0);
	signal(SIGINT, &signal_manager);
	g_pid = 0;
	signal(SIGQUIT, &signal_manager);
	kill(g_pid, SIGQUIT);
	init_history();
}

int	main(int argc, char *argv[], char *envp[])
{
	char		buf[2];
	char		*line;
	t_lstenv	*my_env;

	ft_main_init(&argc, &argv);
	my_env = ft_get_lstenv(envp);
	ft_env(&my_env, 0, INIT);
	buf[1] = '\0';
	my_env = creat_env(envp);
	while (1)
	{
		line = aff_prompt(my_env);
		if (!line)
			break ;
		if (line && *line && *line != '\n')
			ft_parse(line);
		if (line)
			ft_memdel((void **)&line);
	}
	free_history();
	if (line)
		ft_memdel((void **)&line);
	free_environ(my_env);
	return (0);
}
