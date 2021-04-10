#include "../includes/minishell.h"

char **ft_get_mas(int count)
{
	char **res;

	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (0);
	return (res);
}

void ft_check_str_fatal(char *str)
{
	if (!str)
		exit(EXIT_FAILURE);
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
	if (!(*mas))
		return;
	tmp = *mas;
	while (*tmp)
	{
		ft_free_str(tmp);
		tmp++;
	}
	free(*mas);
	*mas = 0;
}

int ft_switch_spec(t_spec_chr *spec, char c)
{
	int f_slash;

	f_slash = 0;
	if (spec->slash == 1 && spec->quote == 0 && spec->quotes == 0)
	{
		spec->slash = 0;
		f_slash = 1;
	}
	if (c == '\\' && spec->quote == 0 && spec->quotes == 0 )
		spec->slash = 1;
	if (spec->quote == 1 && !f_slash && c == '\'' && spec->quotes == 0)
		spec->quote = 0;
	if (spec->quote == 0 && !f_slash && c == '\'' && spec->quotes == 0)
		spec->quote = 1;
	if (spec->quotes == 1 && !f_slash && c == '\"' && spec->quote == 0)
		spec->quotes = 0;
	if (spec->quotes == 0 && !f_slash && c == '\"' && spec->quote == 0)
		spec->quotes = 1;
	if (c == '\\' && spec->quote == 0 && spec->quotes == 0 && f_slash == 1)
		return (1);
	if (c == '\"' && spec->quote == 0 && f_slash == 0)
		return (1);
	if (c == '\'' && spec->quotes == 0 && f_slash == 0)
		return (1);
	return (0);
}

int ft_switch_quotes(int *quote,int *quotes,int slash, char c)
{
	if (*quote == 1 && !slash && c == '\'' && *quotes == 0)
	{
		*quote = 0;
		return (1);
	}
	if (*quote == 0 && !slash && c == '\'' && *quotes == 0)
	{
		*quote = 1;
		return (1);
	}
	if (*quotes == 1 && !slash && c == '\"' && *quote == 0)
	{
		*quotes = 0;
		return (1);
	}
	if (*quotes == 0 && !slash && c == '\"' && *quote == 0)
	{
		*quotes = 1;
		return (1);
	}
	return (0);
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

int ft_switch_slash(t_spec_chr *spec,char c)
{
	if (spec->quotes || spec->quote)
		return (0);
	if ( spec->slash == 1)
		return(spec->slash = 0);
	if (c == '\\')
		return (spec->slash = 1);
	else
		return (spec->slash = 0);
}

int ft_istoken(char *s,int *i,int spec)
{
	int res;
	res = -1;
	if (spec)
	{
		if (!s[*i + 1])
			return (0);
		return (res);
	}
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



int ft_count_args_spec(char *s)
{
	int count;
	int i;
	t_spec_chr spec;
	char debug;
	ft_init_spec(&spec);
	i = 0;
	count = 0;
	while (s[i])
	{
		debug  = s[i];
		if ( (s[i] == '\"' || s[i] == '\'' || s[i] == '\\')
			 && ft_switch_spec(&spec,s[i]))
			count++;
		i++;
	}
	return (count);
}

void ft_del_spec(char **s)
{
	int i;
	int j;
	char *res;
	t_spec_chr spec;
	ft_init_spec(&spec);
	i = 0;
	j = 0;
	res = malloc(ft_strlen(*s) - ft_count_args_spec(*s) + 1);
	if (!res)
		return; //malloc
	while (s[0][j])
	{
		while ( (s[0][j] == '\"' || s[0][j] == '\'' || s[0][j] == '\\')
				&& ft_switch_spec(&spec,s[0][j]) && s[0][j])
			j++;
		if (!s[0][j])
			break;
		res[i++] = s[0][j++];
	}
	res[i] = '\0';
	ft_free_str(s);
	*s = res;
}

char *ft_get_env(char *s,char **env)
{
	int i;
	size_t len;
	char *res;

	i = 0;
	len = ft_strlen(s);
	while (env[i])
	{
		if (!ft_strncmp(s,env[i],len))
			break;
		i++;
	}
	res = env[i];
	if (!res)
		return (0);
	res += len + 1;
	res = ft_strdup(res);
	if (!res)
		return (0); // fail malloc;
	return (res);
}

void ft_del_str_start_end(char **s,int start, int end)
{
	char *res;
	int i;
	int j;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(*s) + end - start + 1);
	while (s[0][i])
	{
		while (i >= start && i < end && s[0][i])
			i++;
		if (!s[0][i])
			break ;
		res[j++] = s[0][i++];
	}
	res[j] = '\0';
	ft_free_str(s);
	*s = res;
}

char *ft_get_insert_env(char **s, int i,char **env)
{
	int end;
	int start;
	char *res;
	char *tmp;
	int k;

	k = 0;
	start = i++;
	end = i;
	while (ft_isalpha(s[0][end]))
		end++;
	res = malloc(end - i + 1);
	if (!res)
		return (0); //no malloc
	while (ft_isalpha(s[0][i]))
		res[k++] = s[0][i++];
	res[k] = '\0';
	tmp = res;
	res = ft_get_env(res,env);
	ft_free_str(&tmp);
	ft_del_str_start_end(s,start,end);
	return (res);
}
void ft_insert_env_value(char **s,int *start,char **value)
{
	char *res;
	int i;
	int k;
	int len;
	int i2;

	i2 = 0;
	i = 0;
	k = 0;
	if (!*value)
		return;
	len = (int)ft_strlen(*s) + (int)ft_strlen(*value) + 1;
	res = malloc(len);
	if (!res)
		return; // malloc
	while (i < len - 1)
	{
		if (k == *start)
			while(value[0][i2])
				res[i++] = value[0][i2++];
		if (i < len - 1)
			res[i++] = s[0][k++];
	}
	ft_free_str(value);
	res[i] ='\0';
	ft_free_str(s);
	*s = res;
	*start += len;
}

void ft_insert_env(char **s,char **env)
{
	int i;
	char *env_var;

	env_var = 0;
	i = 0;
	while (s[0][i])
	{
		if (s[0][i] == '$')
		{
			env_var = ft_get_insert_env(s,i,env);
			ft_insert_env_value(s,&i,&env_var);
		}
		if (!s[0][i])
			break;
		i++;
	}
}

char *ft_get_args_val(char *line, int start, int end,char **env)
{
	int i;
	char *res;
	char *tmp;
	int fix;

	i = 0;
	if (end == start)
		fix = 1;
	else
		fix = 2;
	res = malloc(end - start  + fix);
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
	ft_insert_env(&res,env);
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
		ft_switch_slash(&spec,line[i]);
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

char *ft_get_args_str(char *line, int *i,char **env)
{
	t_spec_chr	spec;
	int start;
	int end;
	char *res;
	char debug;
	res = 0;
	ft_init_spec(&spec);
	start = *i;
	while (line[*i])
	{
		debug = line[*i];
		ft_switch_slash(&spec, line[*i]);
		ft_switch_quotes(&spec.quote, &spec.quotes, spec.slash,line[*i]);

		if ((line[*i] == ' ' && !ft_check_spec(&spec)) || !line[*i + 1])
		{
			end = *i;
			res = ft_get_args_val(line, start, end,env);
			if (line[*i] == ' ')
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
	int fix;
	if (end <= start)
		return (0);
	if (start == end )
		fix = 1;
	else
		fix = 2;
	res = malloc(end - start + fix);
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

char **ft_get_args(char *line, char **env)
{
	int i;
	int count;
	char **args;
	int j;

	j = 0;
	i = 0;
	if (!line)
		return (0);
	count = ft_args_count(line);
	args = ft_get_mas(count);
	if (!args)
		return (0); //fatal exit
	while (j < count)
	{
		args[j] = ft_get_args_str(line, &i,env);
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
	char debug = 0;
	start = *i;
	*token  = -1;
	ft_init_spec(&spec);
	if (!line[*i])
		return ;
	while (line[*i])
	{
		debug = line[*i];
		ft_switch_quotes(&spec.quote, &spec.quotes, spec.slash, line[*i]);
		ft_switch_slash(&spec,line[*i]);
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

int ft_free_bin(char **save_bin,char **bin, char *check, int ret)
{
	ft_free_str(save_bin);
	ft_free_str(bin);
	*bin = check;
	return (ret);
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

int ft_check_run(char *s,t_lstcmds *cmds)
{
	struct stat sb;
	if (!s)
		return 0 ;
	if (stat(s, &sb) == -1)
	{
		cmds->error =  ERR_NO_FILE;
		return 0;
	}
	if (S_IXUSR & sb.st_mode)
		return (1);
	else if (S_IFREG == (sb.st_mode & S_IFMT))
	{
		cmds->error = ERR_NO_PERM;
		return (0);
	}
	else if (S_IFDIR == (sb.st_mode & S_IFMT))
	{
		cmds->error = ERR_IS_DIRECT;
		return (0);
	}
	return (0);
}

int ft_check_bin(char *s)
{
	struct stat sb;
	if (!s)
		return 0 ;
	if (stat(s, &sb) == -1)
		return 0;
	if (S_IXUSR & sb.st_mode)
		return (1);
	else if (S_IFREG == (sb.st_mode & S_IFMT))
		return (ERR_NO_PERM);
	return (0);
}

int ft_check_bins(char **bin, char **bins)
{
	int i;
	char *check;
	char *save_bin;
	int ret;

	check = ft_strjoin("/",*bin);
	save_bin = check;
	ft_check_str_fatal(check);
	i = 0;
	while (bins[i])
	{
		check = ft_strjoin(bins[i], save_bin);
		ft_check_str_fatal(check);
		ret = ft_check_bin(check);
		if (!ret)
			ft_free_str(&check);
		else
			return (ft_free_bin(&save_bin,bin,check,ret));
		check = save_bin;
		i++;
	}
	ft_free_str(&save_bin);
	return (ERR_N0_COMMAND);
}

int ft_get_bin(t_lstcmds *cmds, char **bins)
{
	t_lstcmds *prev;
	prev = cmds->prev;
	if (prev)
		if (prev->token == TOKEN_R_D_OUT || prev->token == TOKEN_R_OUT
			|| prev->token == TOKEN_R_IN)
			return (1);
	if (!ft_strncmp("./", cmds->args[0],2) || ft_strchr(cmds->args[0],'/'))
		return (ft_check_run(cmds->args[0], cmds));
	cmds->error  = ft_check_bins(&cmds->args[0],bins);
	return (0);
}


void ft_is_error_syntax(t_lstcmds *cmds)
{
	if (!cmds->args)
		cmds->error = ERR_SYNTAX_ER;
}



int   ft_check(t_lstcmds *cmds,char **env)
{
	char **bins;

	bins = ft_get_path(env);
	if (!bins)
		return (0); //fatal_exit;
	while (cmds)
	{
		ft_is_error_syntax(cmds);
		if (cmds->args)
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

void ft_strjoin_and_free(char **s1, char *s2)
{
	char *tmp;

	tmp = 0;
	tmp = *s1;
	*s1 = ft_strjoin(*s1,s2);
	ft_free_str(&tmp);
}



char *ft_run_r_in(t_lstcmds *cmds,t_lstcmds *prev)
{
	int fd;
	int byte;
	int bytes;
	char buf[2];
	char *s;

	s = 0;
	bytes = 0;
	fd  = open(cmds->args[0], O_RDONLY);
	while ((byte = read(fd,buf,1)) > 0 )
	{
		buf[1] = '\0';
		ft_strjoin_and_free(&s, buf);
		ft_check_str_fatal(s);
		bytes += byte;
	}
	if (byte < 0)
		printf("fatal"); // ошибку
	write(prev->fds[1],s,bytes); // еще ошибку
	close(prev->fds[1]);
	return (s);
}

int ft_check_open_r_error(char *s,int token)
{
	struct stat sb;
	if (!s)
		return (1) ;
	if (stat(s, &sb) == -1)
		return (0);

	if (S_IFDIR == (sb.st_mode & S_IFMT))
	{
		write(2, MSG_ERR_IS_DIRECT, ft_strlen(MSG_ERR_IS_DIRECT));
		write(2, s, ft_strlen(s));
		write(2,"\n",1);
		return (0);
	}
	if (S_IWUSR != (sb.st_mode & S_IFMT))
	{
		write(2, MSG_ERR_NO_PERM, ft_strlen(MSG_ERR_NO_PERM));
		write(2, s, ft_strlen(s));
		write(2,"\n",1);
		return (0);
	}
	(void)token;
	return (0);
}

int ft_run_r_out(int pipefd,char *filename,int token)
{
	int fd;
	int count;
	char *data;
	data = 0;
	if (ft_check_open_r_error(filename,token))
		return (0);
	if (token == TOKEN_R_OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0) //??
		return (-1);
	if (0 > (count = ft_get_pipe_data(pipefd,&data)))
		return(-1);
	if (0 > write(fd,data,count))
		return (-1);
	close(fd);
	return (0);
}

void ft_dup2(t_lstcmds *cmds, t_lstcmds *prev)
{
	if (cmds->token == TOKEN_PIPE
		|| cmds->token == TOKEN_R_D_OUT
		|| cmds->token == TOKEN_R_OUT)
		dup2(cmds->fds[1],1);
	if (prev)
		if (prev->token == TOKEN_PIPE
			|| prev->token == TOKEN_R_IN)
			dup2(prev->fds[0],0);
}

void ft_fork_command(t_lstcmds *cmd, t_lstcmds *cmds,t_lstcmds *prev,char **env)
{
	pid_t  pid;
	int status;
	pid = fork();
	if (!pid)
	{
		ft_dup2(cmds,prev);
		execve(cmd->args[0],cmd->args,env);
		exit(0);
	}
	waitpid(pid,&status,0);
	cmds->status = status;
	//printf("status = %d\n",status);
}

int ft_is_fork(t_lstcmds *cmds)
{
	t_lstcmds *prev;
	prev = cmds->prev;
	if (cmds->token == TOKEN_R_IN)
		return (0);
	if (prev)
		if (prev->token == TOKEN_R_OUT
			|| prev->token == TOKEN_R_D_OUT)
			return (0);
	if (prev)
		if (prev->token == TOKEN_R_IN)
			return (2);
	return (1);
}

void ft_open_pipe(t_lstcmds *cmds, t_lstcmds *prev)
{
	int ret;

	ret = 0;
	if (prev)
		if (prev->token == TOKEN_R_IN)
			pipe(prev->fds);
	if (ret < 0)
		printf("fatal exit"); //fatal exit;
	if (cmds->token == TOKEN_PIPE
		|| cmds->token == TOKEN_R_OUT
		|| cmds->token == TOKEN_R_D_OUT)
		ret = pipe(cmds->fds);
	if (ret < 0)
		printf("fatal exit"); //fatal exit;
}

void ft_close_pipe(t_lstcmds *cmds, t_lstcmds *prev)
{
	if (cmds->token == TOKEN_PIPE
		|| cmds->token == TOKEN_R_OUT
		|| cmds->token == TOKEN_R_D_OUT)
		close(cmds->fds[1]);
	if (prev)
		if (prev->token == TOKEN_PIPE
			|| prev->token == TOKEN_R_D_OUT
			|| prev->token == TOKEN_R_IN
			|| prev->token == TOKEN_R_OUT)
			close(prev->fds[0]);

}

int ft_is_r_out(t_lstcmds *prev)
{
	if (prev)
		if (prev->token == TOKEN_R_D_OUT || prev->token == TOKEN_R_OUT)
			return (1);
	return (0);
}

int ft_check_error_syntax(t_lstcmds *cmds)
{
	t_lstcmds *next;

	while (cmds)
	{
		next = cmds->prev;
		if(!cmds->args)
		{
			write(2, MSG_ERR_SYNTAX_ERR,
				  ft_strlen(MSG_ERR_SYNTAX_ERR));
			return (1);
		}
		cmds = cmds->next;
	}
	return (0);
}

void ft_run_error(t_lstcmds *cmds)
{
	if (cmds->error == ERR_N0_COMMAND)
	{
		write(2, MSG_ERR_N0_COMMAND, ft_strlen(MSG_ERR_N0_COMMAND));
		write(2, cmds->args[0], ft_strlen(cmds->args[0]));
		write(2,"\n",1);
	}
}

void ft_run_command(t_lstcmds *cmds,char **env)
{
	t_lstcmds *prev;

	if (!ft_check_error_syntax(cmds))
		while (cmds)
		{
			if (cmds->error < 0)
			{
				ft_run_error(cmds);
				cmds = cmds->next;
				continue;
			}
			prev = cmds->prev;
			ft_open_pipe(cmds,prev);
			if (ft_is_fork(cmds) == 1)
				ft_fork_command(cmds,cmds,prev,env);
			if (ft_is_fork(cmds) == 2)
			{
				ft_run_r_in(cmds,prev);
				ft_fork_command(prev, cmds, prev, env);
			}
			if (ft_is_r_out(prev))
				ft_run_r_out(prev->fds[0],cmds->args[0],prev->token);
			ft_close_pipe(cmds,prev);
			cmds = cmds->next;
		}
}

void ft_parse(char *line,char **env)
{
	t_lstcmds *cmds;
	char *str_token;
	int token;
	int i;
	char *tmp;
	cmds = 0;
	i = 0;
	//(void)env;
	while (line[i])
	{
		ft_get_token(line, &i, &str_token, &token);
		if (str_token)
		{
			tmp = str_token;
			str_token = ft_strtrim(str_token, " ");
			ft_free_str(&tmp);
		}
		ft_lstcmdsadd_back(&cmds,ft_lstcmdsnew(ft_get_args(str_token, env),
											   token));
		ft_free_str(&str_token);
	}
	ft_check(cmds,env);
	t_lstcmds *begin;
	begin = cmds;
	int j;
	j = 0;
	while (begin)
	{
		printf("token = %d error = %d || ",begin->token,begin->error);
		if(begin->args)
			while (begin->args[j])
			{
				printf("%s|", begin->args[j]);
				j++;
			}
		j = 0;
		printf("\n");
		begin = begin->next;
	}
	ft_run_command(cmds,env);
	ft_lstcmdsdel(&cmds);
}

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
//	int fd1[2];
//	//int fd2[2];
//	int fd;
//	char buf[2];
//	char *s;
//	s = 0;
//	//echo test | grep -e test -e ls < test
//	char *grep[6];
//	grep[0] = "/usr/bin/grep";
//	grep[1] = "-e";
//	grep[2] = "test";
//	grep[3] = "-e";
//	grep[4] = "ls";
//	grep[5] = 0;
//	pipe(fd1);
//
//	fd = open("/Users/aleksandrsamkov/newshell/test",O_RDONLY);
//	while (read(fd,buf,1) > 0)
//	{
//		buf[1] = '\0';
//		s = ft_strjoin(s,buf);
//	}
//	printf("%zd\n",write(fd1[1],"ls",2));
//	close(fd1[1]);
//	if (!fork())
//	{
//		dup2(fd1[0],0);
//		execve(grep[0],grep,env);
//		exit(0);
//	}
//	wait(0);
//	close(fd1[1]);
//
//}

//int main (int argc, char **argv, char **env)
//{
//	(void )argv;
//	(void )argc;
//	char *s = "$PATH";
//	ft_insert_env(&s,env);
//	printf("%s\n",s);
//}
