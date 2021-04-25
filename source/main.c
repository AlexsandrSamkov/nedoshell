#include "../includes/minishell.h"
void ft_signal_hook()
{
	ft_putstr_fd("\n",1);
}

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



void	ft_wait_command(void)
{
	char	byte;
	char	buf[2];
	char	*command;
	char	*tmp;
	signal (SIGINT, ft_signal_hook);
	command = 0;
	tmp = 0;
	buf[1] = '\0';
	write(0, "\x1b[31m", 5);
	write(0, "Wait CMD\U0001f408: ", 14);
	write(0, "\x1b[94m", 5);
	while ((byte = read(0,buf,1)) > 0)
	{
		if (buf[0] == '\n' && command == 0)
		{
			write(0, "\x1b[31m", 5);
			write(0, "Wait CMD\U0001f408: ", 14);
			write(0, "\x1b[94m", 5);
			continue ;
		}
		else if (buf[0] == '\n')
		{
			ft_parse(command);
			command = ft_free(command);
			write(0, "\x1b[31m", 5);
			write(0, "Wait CMD\U0001f408: ", 14);
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

static int	process(int sign_num)
{
	int status;
	if (sign_num == SIGQUIT)
	{
		kill(gl_pid, sign_num);
		ft_putstr_fd("Quit: 3\n", 1);
		status = 131;

		gl_pid = 0;
		ft_errno(status, SET);
		return status;
	}
	else if (sign_num == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		status = 130;
		ft_errno(status, SET);
		return status;
	}
	return 0;
}

void		signal_manager(int sign_num)
{
	t_cmdline	*l;
	char	buf[2];
	int status = 0;
	//sign_num == SIGINT  ||
	if ((sign_num == SIGQUIT && gl_pid != 0)
	|| (sign_num == SIGINT && gl_pid != 0) )
		status = process(sign_num);
	else
	{
		if (sign_num == SIGINT)
		{
			(void)sign_num;
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
}

int	main(int argc, char *argv[], char *envp[])
{
	char		buf[2];
	char		*command;
	char		*tmp;
	char		*line;
	t_lstenv	*my_env;

	(void)argc;
	(void)argv;

	ft_pid_mass(INIT,0);
	signal(SIGINT, &signal_manager);

	gl_pid = 0;
	signal(SIGQUIT, &signal_manager);
	kill(gl_pid, SIGQUIT);
	my_env = ft_get_lstenv(envp);
	ft_env(&my_env, 0, INIT);
	command = 0;
	tmp = 0;
	buf[1] = '\0';

	my_env = creat_env(envp);
	init_history();
	while (1)
	{
		if (!(line = aff_prompt(my_env)))
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

// int	main(int argc, char *argv[], char *env[])
// {
// 	t_lstenv	*lstenv;
//
// 	(void)argc;
// 	(void)argv;
// 	ft_pid_mass(INIT,0);
// 	//ft_print_promt();
// 	signal (SIGINT, ft_signal_hook);
// 	lstenv = ft_get_lstenv(env);
// 	ft_env(&lstenv, 0, INIT);
// 	ft_wait_command();
// }

//  int main (int argc, char **argv, char **env)
//  {
//  	(void)argc;
//  	(void)argv;
//  	int fd1[2];
//  	//int fd2[2];
//  	char *cat[3];
//  	char *wc[2];
//  	char *ls[2];
//  	char *yes[2];
//  	char *head[2];
//  	cat[0] = "/bin/cat";
//  	cat[1] = "-e";
//  	cat[2] = 0;
//  	wc[0] = "/usr/bin/wc";
//  	wc[1] = 0;
//  	ls[0] = "/bin/ls";
//  	ls[1] = 0;
//  	head[0] = "/usr/bin/head";
//  	head[1] = 0;
//  	yes[0] = "/usr/bin/yes";
//  	yes[1] = 0;

//  	pipe(fd1);
// 	 if (!fork())
// 	 {
// 		dup2(fd1[1],1);

// 		execve(yes[0],yes,env);
// 	 }
//  	if (!fork())
// 	{
// 		dup2(fd1[0],0);

// 		execve(head[0],head,env);
// 	}

//  	wait (0);
// 	while (1);

//  }


//ait CMD🐈: echo hello
//hello
//		Wait CMD🐈: echo hello hello
//		hello hello
//		Wait CMD🐈: echo -n hello hello
//		hello helloWait CMD🐈: echo -n -n hello hello
//-n hello helloWait CMD🐈: echo -nn hello hello
//-nn hello hello
//		Wait CMD🐈: echo -n1 hello hello
//-n1 hello hello
//		Wait CMD🐈: echo
//
//		Wait CMD🐈: echo -n
//		Wait CMD🐈: echo -n " " " "
//Wait CMD🐈: echo -n "" ""
//Wait CMD🐈: echo -n $TEST $TEST
//-n
//bash-3.2$ exit 1 2
//exit
//		bash: exit: too many arguments
//		bash-3.2$ exit 1 str
//		exit
//bash: exit: too many arguments
//		bash-3.2$ exit str 1
//exit
//		bash: exit: str: numeric argument required
//➜  ~ bash
//		bash-3.2$ exit str str