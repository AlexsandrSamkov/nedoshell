#include "libs/libft/libft.h"
#include "stdio.h"

void test(char **env)
{
	pid_t pid;
	char *arg[2];
	int pipes[2];
	arg[0] = "/bin/ls";
	arg[1] = 0;
	pid = fork();
	pipe(pipes);
	dup2(pipes[0],0);
	close(pipes[1]);
	close(pipes[0]);
	if (pid == 0)
	{
		execve(arg[0],arg,env);
	}
	wait(0);

}

int main(int argc,char ** argv, char **env)
{
	(void)argv;
	(void)argc;
	char buff[2];
	char *tmp;
	char *command;
	command = 0;
	tmp = 0;
	buff[1] = '\0';
	while (read(0,buff,1)> 0)
	{
		tmp = command;
		command = ft_strjoin(command,buff);
		free(tmp);
		tmp = 0;
		if (!ft_strncmp(command,"ls",2))
		{
			test(env);
		}
		if (buff[0] == '\n')
		{
			write(1,command,ft_strlen(command));
			free(command);
			command = 0;
		}
	}
}