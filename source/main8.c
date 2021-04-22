

#include "../includes/minishell.h"
void ft_signal_hook()
{
	ft_putstr_fd("\n",1);
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



int	main(int argc, char *argv[], char *env[])
{
	t_lstenv	*lstenv;

	(void)argc;
	(void)argv;
	signal (SIGINT, ft_signal_hook);
	lstenv = ft_get_lstenv(env);
	ft_env(&lstenv, 0, INIT);
	ft_wait_command();
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


//int ft_is_tokent(char *s, int *i)
//{
//	if (s[*i] == ';'
//		|| (s[*i] == '|' &&  s[*i + 1] != '|'))
//		return (1);
//
//	if ((s[*i] == '<' &&  s[*i + 1] == '<')
//		|| (s[*i] == '>' && s[*i + 1] == '>')
//		|| (s[*i] == '|' && s[*i + 1] == '|')
//		|| (s[*i] == '&' && s[*i + 1] != '&'))
//	{
//		(*i)++;
//		return (1);
//	}
//	return (0);
//}
//
//int ft_check_syntax_err(char *s)
//{
//	t_spec_chr *spec;
//	int token;
//	int i;
//	int space;
//	int check;
//	char debug;
//
//	check = 0;
//	space = 1;
//	spec = ft_init_spec();
//	token = 0;
//	i = 0;
//	while (s[i])
//	{
//		debug = s[i];
//		ft_switch_quotes(spec,s[i]);
//		if (s[i] != ' ' && s[i] != '|' && s[i] != ';'
//			&& s[i] != '&' && s[i] != '>' && s[i] != '<'
//			&& !ft_check_spec(spec))
//			space = 0;
//		if (s[i] != ' ' && !ft_check_spec(spec))
//		{
//			check = ft_is_tokent(s, &i,);
//			if (check)
//			{
//				if (token == 1 || space)
//					return (1);
//				token = 1;
//			} else
//				token = 0;
//		}
//		if (!s[i])
//			return (-1);
//		ft_switch_slash(spec, s[i]);
//		i++;
//	}
//	return (-1);
//}
//
//int main()
//{
//	char *s = "asdasd>> >> asdasd";
//	int check = 0;
//	check  = ft_check_syntax_err(s);
//	if (check == -1)
//		printf("%s\n",s);
//}

// int main (int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	int fd1[2];
// 	//int fd2[2];
// 	char *cat[3];
// 	char *wc[2];
// 	char *ls[2];
// 	char *yes[2];
// 	char *head[2];
// 	char *ps[2];
// 	cat[0] = "/bin/cat";
// 	cat[1] = "-e";
// 	cat[2] = 0;
// 	wc[0] = "/usr/bin/wc";
// 	wc[1] = 0;
// 	ls[0] = "/bin/ls";
// 	ls[1] = 0;
// 	head[0] = "/usr/bin/head";
// 	head[1] = 0;
// 	yes[0] = "/usr/bin/yes";
// 	yes[1] = 0;
// 	ps[0] = "/bin/ps";
// 	ps[1] = 0;
// 	pipe(fd1);
// 	 if (!fork())
// 	 {
// 		 dup2(fd1[0],0);
// 		close(fd1[0]);
// 		close(fd1[1]);
// 		execve(head[0],head,env);
// 	 }
// 	 close(fd1[0]);
// 	if (!fork())
// 	{
// 		 dup2(fd1[1],1);
// 		 close(fd1[0]);
// 		 close(fd1[1]);
// 		 execve(yes[0],yes,env);
// 	}
// 	close(fd1[1]);
// 	wait (0);
// 		if (!fork())
// 	{
// 		 execve(ps[0],ps,env);
// 	}
// 	wait (0);
// }