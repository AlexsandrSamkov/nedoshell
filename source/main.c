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
			ft_parse(&command);
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
	//ft_print_promt();
	signal (SIGINT, ft_signal_hook);
	lstenv = ft_get_lstenv(env);
	ft_env(&lstenv, 0, INIT);
	ft_wait_command();
}

//  int main (int argc, char **argv, char **env)
//  {
//  	(void)argc;
//  	(void)argv;
//  	int fd1[2];
//  	int fd2[2];
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
//  	int fd;
	
//  	pipe(fd1);
// 	 close(fd1[0]);
// 	 if (!fork())
// 	 {
// 		fd1[1] = open("ls", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	 }
//  	if (!fork())
// 	{
// 		dup2(fd1[1],1);
// 		close(fd1[1]);
// 		execve(ls[0],ls,env);
// 	}
//  	wait (0);
//  }