#include "../includes/minishell.h"

char **ft_get_mas(int count)
{
	char **res;

	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (0);
	return (res);
}


void ft_free_str(char **s)
{
	if (*s)
	{
		free(*s);
		*s = 0;
	}
}

void ft_free_mas(char ***mas)
{
	char **tmp;

	tmp = *mas;
	while (*tmp)
	{
		ft_free_str(tmp);
		tmp++;
	}
	free(*mas);
	*mas = 0;
}

void ft_switch_quotes(int *quote,int *quotes,int slash, char c)
{
	if (*quote == 1 && !slash && c == '\'')
	{
		*quote = 0;
		return ;
	}
	if (*quote == 0 && !slash && c == '\'')
	{
		*quote = 1;
		return ;
	}
	if (*quotes == 1 && !slash && c == '\"')
	{
		*quotes = 0;
		return ;
	}
	if (*quotes == 0 && !slash && c == '\"')
	{
		*quotes = 1;
		return ;
	}
}

t_lstcmds	*ft_lstcmdslast(t_lstcmds *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstcmdsadd_back(t_lstcmds **lst, t_lstcmds *new)
{
	t_lstcmds *tmp;


	if (*lst)
	{
		tmp = ft_lstcmdslast(*lst);
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*lst = new;
}

t_lstcmds	*ft_lstcmdsnew(char **args, int token)
{
	t_lstcmds *tmp;

	tmp = 0;
	if ((tmp = malloc(sizeof(t_lstcmds))))
	{
		tmp->args = args;
		tmp->next = 0;
		tmp->prev = 0;
		tmp->token = token;
		tmp->error = 0;
		tmp->fds[0] = -1;
		tmp->fds[1] = -1;
		tmp->status = 0;
	}
	return (tmp);
}

void ft_lstcmdsdel(t_lstcmds **cmds)
{
	t_lstcmds *begin;
	t_lstcmds *tmp;
	begin =  *cmds;

	*cmds = 0;
	while (begin)
	{
		tmp = begin;
		begin = begin->next;
		ft_free_mas(&tmp->args);
		free(tmp);
		tmp = 0;
	}
}

int ft_switch_slash(int *slash,char c)
{
	if ( *slash == 1)
		return(*slash = 0);
	if (c == '\\')
		return (*slash = 1);
	else
		return (*slash = 0);
}

int ft_istoken(char *s,int *i,int spec)
{
	int res;
	res = -1;
	if (spec)
		return (res);
	if ((s[*i] == '>' && (s[(*i) + 1]) == '>'))
	{
		res = TOKEN_R_D_OUT;
	}
	else if (s[*i] == ';')
		res = TOKEN_BIN;
	else if (s[*i] == '|')
		res = TOKEN_PIPE;
	else if (s[*i] == '<')
		res = TOKEN_R_IN;
	else if (s[*i] == '>')
		res = TOKEN_R_OUT;
	else if (!s[*i + 1])
		return (0);
	return (res);
}

void ft_init_spec(t_spec_chr *spec)
{
	spec->quote = 0;
	spec->quotes = 0;
	spec->slash = 0;
}

int ft_check_spec(t_spec_chr *spec)
{
	if (!spec->quote && !spec->quotes && !spec->slash)
		return (0);
	return (1);
}

int ft_count_tokens(char *line)
{
	int i;
	int count;
	int token;
	t_spec_chr spec;

	token = -1;
	ft_init_spec(&spec);
	i = 0;
	count = 1;
	while (line[i])
	{
		ft_switch_slash(&spec.slash,line[i]);
		ft_switch_quotes(&spec.quotes, &spec.quote, spec.slash, line[i]);
		token = ft_istoken(line,&i,ft_check_spec(&spec));
		if (token >= 5)
		{
			i++;
			count++;
		}
		else if (token <= 5 && 0 < token)
			count++;
		i++;
	}
	return (count);
}

int ft_count_args_spec(char *str)
{
	int count;
	int i;
	t_spec_chr spec;

	ft_init_spec(&spec);
	i = 0;
	count = 0;
	while (str[i])
	{
		if(ft_switch_slash(&spec.slash,str[i]))
		{
			str++;
			continue;
		}
		if ((str[i] == '\\' || str[i] == '\"'
		|| str[i] == '\'') && !spec.slash)
			count++;
		i++;
	}
	return (count);
}

void ft_del_spec(char **str)
{
	int		i;
	int		slash;
	int 	j;
	int		count;
	char 	*tmp;

	i = 0;
	j = 0;
	slash = 0;
	tmp = str[0];
	count = (int)ft_strlen(tmp) - ft_count_args_spec(tmp) + 1;
	str[0] = malloc(count);
	if (!*str)
		return ; // exit fatal;
	while (j < count - 1)
	{
		if(ft_switch_slash(&slash, tmp[i]))
			i++;
		if (((tmp[i]== '\"'
		|| tmp[i] == '\'') && !slash) || !tmp[i])
		{
			i++;
			continue;
		}
		slash = 0;
		str[0][j++] = tmp[i++];
	}
	str[0][j] = '\0';
	ft_free_str(&tmp);
}

char *ft_get_args_val(char *line, int start, int end)
{
	int i;
	char *res;
	char *tmp;
	i = 0;
	res = malloc(end - start  + 1);
	if (!res)
		return (0);  //fatal exit;
	while (start <= end && line[start])
		res[i++] = line[start++];
	res[i] = '\0';
	tmp = res;
	res = ft_strtrim(res," ");
	ft_free_str(&tmp);
	if(!res)
		return (0); //fatal exit;
	ft_del_spec(&res);
	return (res);
}

int ft_args_count(char *line)
{
	int count;
	int i;
	t_spec_chr spec;

	ft_init_spec(&spec);
	i = 0;
	count = 1;

	while (line[i])
	{
		ft_switch_slash(&spec.slash,line[i]);
		ft_switch_quotes(&spec.quote, &spec.quotes,spec.slash,line[i]);
		if (!ft_check_spec(&spec) && line[i] == ' ')
		{
			while (line[i] && line[i] == ' ')
				i++;
			if (!line[i])
				break;
			count++;
			continue;
		}
		i++;
	}
	return(count);
}

char *ft_get_args_str(char *line, int *i)
{
	t_spec_chr	spec;
	int start;
	int end;
	char *res;

	res = 0;
	ft_init_spec(&spec);
	start = *i;
	while (line[*i])
	{
		ft_switch_slash(&spec.slash, line[*i]);
		ft_switch_quotes(&spec.quote, &spec.quotes, spec.slash,line[*i]);
		if ((line[*i] == ' ' && !ft_check_spec(&spec)) || !line[*i + 1])
			{
				end = *i;
				res = ft_get_args_val(line,start,end);
				(*i)++;
				break;
			}
		(*i)++;
	}
	return (res);
}

char *ft_get_str_token(char *line, int start, int end)
{
	char *res;
	int i;
	if (end < 0)
		return (0);
	res = malloc(end - start + 1);
	if (!res)
		return (0); // сделать exit_fatal;
	i = 0;
	while (start <= end && line[start])
		res[i++] = line[start++];
	res[i] = '\0';
	return (res);
}

int ft_get_token_end(int token, int *i,char *line)
{
	int res;

	res = *i;
	if (!line[*i + 1] && token  == 0)
	{
		(*i)++;
		return (res);
	}
	if (token >= 5)
	{
		res--;
		*i += 2;
		return(res);
	}
	else if (token >= 0)
	{
		res--;
		(*i)++;
		return (res);
	}
	return (res);
}

char **ft_get_args(char *line)
{
	int i;
	int count;
	char **args;
	int j;

	j = 0;
	i = 0;
	count = ft_args_count(line);
	args = ft_get_mas(count);
	if (!args)
		return (0); //fatal exit
	while (j < count)
	{
		args[j] = ft_get_args_str(line, &i);
		if (!args[j])
			return (0); //fatal exit
		j++;
	}
	args[j] = 0;
	return(args);

}
void ft_get_token(char *line, int *i, char **res, int *token)
{
	t_spec_chr	spec;
	int			start;
	int			end;

	start = *i;
	*token  = -1;
	ft_init_spec(&spec);
	if (!line[*i])
		return ;
	while (line[*i])
	{
		ft_switch_quotes(&spec.quote, &spec.quotes, spec.slash, line[*i]);
		ft_switch_slash(&spec.slash,line[*i]);
		*token = ft_istoken(line,i,ft_check_spec(&spec));
		if ( 0 <= *token  || !line[*i + 1])
			{
				end = ft_get_token_end(*token,i,line);
				*res = ft_get_str_token(line, start, end);
				return ;
			}
		(*i)++;
	}
}


char **ft_get_path(char **env)
{
	char **res;
	char *tmp;
	int i;

	i = 0;
	while(env[i])
	{
		if (!ft_strncmp(env[i],"PATH=",5))
			break;
		i++;
	}
	tmp = env[i];
	tmp += 5;
	res = ft_split(tmp,':');
	if (!res)
		return (0); //fatal exit
	return (res);
}

int ft_free_bin(char **save_bin,char **bin, char *check)
{
	ft_free_str(save_bin);
	ft_free_str(bin);
	*bin = check;
	return (1);
}

void ft_is_bin(t_lstcmds *cmds,char **env)
{
	if (!ft_strncmp(cmds->args[0],"cd",ft_strlen(cmds->args[0])))
		printf("is cd");
	else if (!ft_strncmp(cmds->args[0],"echo",ft_strlen(cmds->args[0])))
		printf("is echo");
	else if (!ft_strncmp(cmds->args[0],"pwd",ft_strlen(cmds->args[0])))
		printf("is pwd");
	else if (!ft_strncmp(cmds->args[0],"export",ft_strlen(cmds->args[0])))
		printf("is export");
	else if (!ft_strncmp(cmds->args[0],"unset",ft_strlen(cmds->args[0])))
		printf("is unset");
	else if (!ft_strncmp(cmds->args[0],"env",ft_strlen(cmds->args[0])))
		printf("is env");
	else if (!ft_strncmp(cmds->args[0],"exit",ft_strlen(cmds->args[0])))
		printf("is exit");
	execve(cmds->args[0],cmds->args,env);
}

int ft_check_bin(char **bin, char **bins)
{
	int i;
	struct stat buf;
	char *check;
	char *save_bin;

	check = ft_strjoin("/",*bin);
	save_bin = check;
	if (!check)
		return (0); //fatal exit
	i = 0;
	while (bins[i])
	{
		check = ft_strjoin(bins[i], save_bin);
		if (!check)
			return (0); //fatal exit
		if (lstat(check,&buf))
			ft_free_str(&check);
		else
			return (ft_free_bin(&save_bin,bin,check));
		check = save_bin;
		i++;
	}
	ft_free_str(&save_bin);
	return (0);
}

int ft_get_bin(t_lstcmds *cmds, char **bins)
{
	struct stat buf;
	t_lstcmds *prev;
	prev = cmds->prev;
	if (prev)
		if (prev->token == TOKEN_R_D_OUT || prev->token == TOKEN_R_OUT
		|| prev->token == TOKEN_R_IN)
		return (1);
	if (!lstat(cmds->args[0], &buf))
		return (1);
	if (ft_check_bin(&cmds->args[0],bins))
		return (1);
	cmds->error = 127;
	return (0);
}

int   ft_check(t_lstcmds *cmds,char **env)
{
	char **bins;
	bins = ft_get_path(env);
	if (!bins)
		return (0); //fatal_exit;
	while (cmds)
	{
		ft_get_bin(cmds,bins);
		cmds = cmds->next;
	}
	ft_free_mas(&bins);
	return(0);
}




int ft_get_pipe_data(int fd, char **data)
{
	int byte;
	int bytes;
	char buf[2]; //мб увеличть буфер???

	char *tmp;
	bytes = 0;
	while ((byte = read(fd,buf,1)) > 0)
	{
		buf[1] = '\0';
		tmp = *data;
		if (!(*data = ft_strjoin(*data,buf)))
			return (-1);
		ft_free_str(&tmp);
		bytes += byte;

	}
	if (byte < 0)
		return (-1);
	return (bytes);
}

int ft_run_r_out(int pipefd,char *filename,int token)
{
	int fd;
	int count;
	char *data;
	(void)token;
	data = 0;
	if ((fd = open(filename,O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0) //??
		return (-1);
	if (0 > (count = ft_get_pipe_data(pipefd,&data)))
		return(-1);
	if (0 > write(fd,data,count))
		return (-1);
	close(fd);
	return (0);
}





void ft_fork_command(t_lstcmds *cmds,t_lstcmds *prev,char **env)
{
	pid_t  pid;
	int status;
	pid = fork();
	if (!pid)
	{
		if (cmds->token == TOKEN_PIPE || cmds->token == TOKEN_R_D_OUT
			|| cmds->token == TOKEN_R_OUT)
			dup2(cmds->fds[1],1);
		if (prev)
			if (prev->token == TOKEN_PIPE)
				dup2(prev->fds[0],0);
		execve(cmds->args[0],cmds->args,env);
	}
	waitpid(pid,&status,0);
	cmds->status = status;
	printf("status = %d\n",status);
}

int ft_is_fork(t_lstcmds *prev)
{
	if (prev)
		if (prev->token == TOKEN_R_OUT || prev->token == TOKEN_R_D_OUT)
			return (0);
	return (1);
}

void ft_run_command(t_lstcmds *cmds,char **env)
{
	t_lstcmds *prev;

	while (cmds)
	{
		prev = cmds->prev;
		if (cmds->token == TOKEN_PIPE || cmds->token == TOKEN_R_OUT
		|| cmds->token == TOKEN_R_D_OUT)
			pipe(cmds->fds);
		if (ft_is_fork(prev))
			ft_fork_command(cmds,prev,env);
		else
			ft_run_r_out(prev->fds[0],"hello.txt",1);
		if (cmds->token == TOKEN_PIPE|| cmds->token == TOKEN_R_OUT
			|| cmds->token == TOKEN_R_D_OUT)
			close(cmds->fds[1]);
		if (prev)
			if (prev->token == TOKEN_PIPE || prev->token == TOKEN_R_D_OUT
			|| prev->token == TOKEN_R_OUT)
			close(prev->fds[0]);
		cmds = cmds->next;
	}
}

void ft_parse(char *line,char **env)
{
	int count;
	t_lstcmds *cmds;
	char *str_token;
	int token;
	int i;
	char *tmp;
	cmds = 0;
	i = 0;
	count = ft_count_tokens(line);
	while ( 0 < count)
	{
		ft_get_token(line, &i, &str_token, &token);
		if (!str_token)
			break ;
		tmp = str_token;
		str_token = ft_strtrim(str_token," ");
		ft_free_str(&tmp);
		ft_lstcmdsadd_back(&cmds,ft_lstcmdsnew(ft_get_args(str_token), token));
		ft_free_str(&str_token);
		count--;
	}
	//(void)env;
	ft_check(cmds,env);
	t_lstcmds *begin;
	begin = cmds;
	int j;
	j = 0;
	while (begin)
	{
		while (begin->args[j])
		{
			printf("%s||", begin->args[j]);
			j++;
		}
		j = 0;
		printf("\n");
		begin = begin->next;
	}
	ft_run_command(cmds,env);
	ft_lstcmdsdel(&cmds);
}
//
int main(int argc,char *argv[],char *env[])
{
	(void)argc;
	(void)argv;
	char byte;
	char buf[2];
	char *command;
	char *tmp;

	command = 0;
	tmp = 0;
	buf[1] = '\0';
	write(0,"> ",2);
	while ((byte = read(0,buf,1)) > 0)
	{
		if (buf[0] == '\n' && command == 0)
		{
			write(0,"> ",2);
			continue;
		}
		else if (buf[0] == '\n')
		{

			ft_parse(command, env);
			ft_free_str(&command);
			write(0,"> ",2);
		}
		else
		{
			tmp = command;
			command = ft_strjoin(command,buf);
			ft_free_str(&tmp);
		}
	}
}

//int main (int argc,char **argv,char **env)
//{
//	(void)argc;
//	(void)argv;
////	int fd[2];
//	char *a1[3];
//	char *a2[3];
//	a1[0] = "/bin/ls";
//	a1[1] = "d";
//	a1[2] = 0;
//	a2[0] = "/bin/cat";
//	a2[1] = "-e";
//	a2[2] = 0;
//	pid_t  pid;
//	int status;
//	status = 0;
//	if (!(pid = fork()))
//	{
//		execve(a1[0],a1,env);
//	}
//	waitpid(pid,&status,0);
//	printf("%d\n",status);
////	if(!fork())
////	{
////		dup2(fd[1],1);
////		execve(a1[0],a1,env);
////		exit(0);
////	}
////	wait(0);
////	close(fd[1]);
////	ft_run_r_out(fd[0],"hello.txt",1);
////	char buf[2];
////	while ((read(fd[0],buf,1) > 0))
////	{
////		write(1,buf,1);
////	}
//}
