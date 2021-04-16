#include "../includes/minishell.h"

void	ft_wait_command(void)
{
	char	byte;
	char	buf[2];
	char	*command;
	char	*tmp;

	command = 0;
	tmp = 0;
	buf[1] = '\0';
	write(0, "\x1b[31m", 5);
	write(0, "Wait CMD: ", 10);
	write(0, "\x1b[94m", 5);
	while ((byte = read(0,buf,1)) > 0)
	{
		if (buf[0] == '\n' && command == 0)
		{
			write(0, "\x1b[31m", 5);
			write(0, "Wait CMD: ", 10);
			write(0, "\x1b[94m", 5);
			continue ;
		}
		else if (buf[0] == '\n')
		{
			ft_parse(&command);
			command = ft_free(command);
			write(0, "\x1b[31m", 5);
			write(0, "Wait CMD: ", 10);
			write(0, "\x1b[94m", 5);
		}
		else
		{
			tmp = command;
			command = ft_strjoin(command, buf);
			tmp = ft_free(tmp);
		}
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_lstenv	*lstenv;

	(void)argc;
	(void)argv;
	lstenv = ft_get_lstenv(env);
	ft_env(&lstenv, 0, INIT);
	ft_wait_command();
}
