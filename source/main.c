/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:41:29 by weambros          #+#    #+#             */
/*   Updated: 2021/02/27 03:23:16 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_run_command(char **env)
{
//	pid_t pid;
	char *arg[2];
	arg[0] = "/bin/pwd";
	arg[1] = "";
	pid_t pid;
	int status;
	int pipes[2];
	pipe(pipes);
	dup2(pipes[1],1);
	//close(pipes[1]);
	//close(pipes[0]);
	//close(pipes[1]);
	pid = fork();
	if (!pid)
	{
		execve(arg[0], arg, env);
		//close(pipes[])
		exit(0);
	}
	waitpid(pid, &status, 0);
}
//void test(char **env)
//{
//	char *arg[2];
//	arg[0] = "/bin/ls";
//	arg[1] = " ";
//	execve(arg[0], arg, env)
//}
int	main(int argc, char **argv, char **envv)
{

	char buff[2];
	//char **bin;
	buff[0] = ' ';
	buff[1] = '\0';

	(void)argc;
	(void)envv;
	(void)**argv;
	char *command;
	char *tmp;
	command = 0;
	tmp = 0;
	int i;
	i = 0;
	pid_t		wpid;
	int			status;
//	bin = ft_parse_bin(envv);
//	while (bin[i])
//	{
//		printf("%s\n",bin[i]);
//		i++;
//	}

	write(1,"> ",2);
	while (read(0,buff,1) > 0)
	{
		tmp = command;
		if (buff[0] != '\n')
		{
			command = ft_strjoin(command, buff);
			free(tmp);
		}
		if (buff[0] == '\n')
		{
			if (!ft_strncmp("ls",command,2))
			{
					ft_run_command(envv);
			}
			else
			write(1, command, ft_strlen(command));
			write(1, "\n> ", 3);
			free(command);
			command = 0;
		}
	}
	while ((wpid = wait(&status)) > 0)
		NULL;

}