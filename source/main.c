#include "../includes/minishell.h"

char	**ft_get_mas(int count)
{
	char	**res;

	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (0);
	return (res);
}


int ft_is_no_fork(char *s)
{
	if (!s)
		return (0);
	if ((!ft_strncmp("unset",s , ft_strlen(s)) && ft_strlen(s) == 5)
	|| (!ft_strncmp("UNSET",s , ft_strlen(s)) && ft_strlen(s) == 5)
	|| (!ft_strncmp("export",s, ft_strlen(s)) && ft_strlen(s) == 6)
	|| (!ft_strncmp("EXPORT",s, ft_strlen(s)) && ft_strlen(s) == 6)
    || (!ft_strncmp("cd",s, ft_strlen(s)) && ft_strlen(s) == 2)
    || (!ft_strncmp("CD",s, ft_strlen(s)) && ft_strlen(s) == 2))
		return (1);
	return (0);
}

int ft_unset(char **args)
{
	int i;
	int ret;

	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!ft_is_env_key(args[i]))
		{
			ft_put_error(MSG_ERR_UNSET);
			ft_put_error(args[i]);
			ft_put_error(MSG_ERR_NOT_VALID_ID);
			ft_put_error("\n");
			ret = 1;
			break;
		}
		else
			ft_env(0,args[i],UNSET);
		i++;
	}
	return(ret);
}

void ft_put_error(char *s)
{
	int len;

	len = (int)ft_strlen(s);
	if (!s || !len)
		return;
	if (write(2,s, ft_strlen(s)) < 0)
		return; // ошибка
}

int ft_errno(int n, char f)
{
	static int err;
	if (f == SET)
		err = n;
	return (err);
}

void ft_check_str_fatal(char *str)
{
	if (!str)
		exit(EXIT_FAILURE);
}

void *ft_free(void *s)
{
	if (s)
	{
		free(s);
		s = 0;
	}
	return (0);
}

void ft_free_mas(char ***mas)
{
	char **tmp;
	if (!(*mas))
		return;
	tmp = *mas;
	while (*tmp)
	{
		*tmp = (char *)ft_free(*tmp);
		tmp++;
	}
	free(*mas);
	*mas = 0;
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
	tmp = malloc(sizeof(t_lstcmds));
	if (tmp)
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
	if (spec->slash == 1)
		return(spec->slash = 0);
	if (spec->quote)
		return (0);
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
		debug = s[i];
		ft_switch_quotes(&spec.quote,&spec.quotes,spec.slash,s[i]);
		if((s[i] == '\"' && !spec.quote && !spec.slash)
		|| (s[i] == '\'' && !spec.quotes && !spec.slash)
		|| (s[i] == '\\' && !spec.quotes && !spec.quote && !spec.slash))
			count++;
		ft_switch_slash(&spec,s[i]);
		i++;

	}
	return (count);
}

void ft_del_spec(char **s)
{
	int i;
	int j;
	char *res;
	char debug;
	t_spec_chr spec;
	ft_init_spec(&spec);
	i = 0;
	j = 0;
	res = malloc(ft_strlen(*s) - ft_count_args_spec(*s) + 1);
	if (!res)
		return; //malloc
	while (s[0][j])
	{
		ft_switch_quotes(&spec.quote,&spec.quotes,spec.slash,s[0][j]);
		debug = s[0][j];
		if (!((s[0][j] == '\"' && !spec.quote && !spec.slash)
		|| (s[0][j] == '\'' && !spec.quotes && !spec.slash)
		|| (s[0][j] == '\\' && !spec.quote && !spec.slash)))
			res[i++] = s[0][j];
		ft_switch_slash(&spec,s[0][j]);
	 		j++;
	}
	res[i] = '\0';
	*s = ft_free(*s);
	*s = res;
}

t_lstenv *ft_lstenv_new(char *key, char *value)
{
	t_lstenv *new;

	new = malloc(sizeof (t_lstenv));
	if (!new)
		return (0);
	new->key = key;
	new->value = value;
	new->next = 0;
	return (new);
}

t_lstenv *ft_lstenv_last(t_lstenv *lstenv)
{
	if (!lstenv)
		return (0);
	while (lstenv->next)
		lstenv = lstenv->next;
	return (lstenv);
}

void ft_lstenv_add_back(t_lstenv **lstenv, t_lstenv *new)
{
	t_lstenv *begin;

	begin = *lstenv;
	if (begin)
	{
		begin = ft_lstenv_last(begin);
		begin->next = new;
	}
	else
		*lstenv = new;
}

void ft_lstenv_free(t_lstenv **del)
{
	t_lstenv *tmp;

	tmp = *del;
	tmp->key = ft_free(tmp->key);
	tmp->value = ft_free(tmp->value);
	free(*del);
	*del = 0;
}

char *ft_lstenv_del_key(t_lstenv **env, char *key)
{
	t_lstenv *begin;
	t_lstenv *tmp;
	t_lstenv *del;
	begin = *env;
	tmp = 0;
	if (!ft_strncmp(begin->key, key, ft_strlen(begin->key))
		&& ft_strlen(begin->key) == ft_strlen(key) && !begin->next)
	{
		ft_lstenv_free(env);
		return (0);
	}
	while (begin)
	{
		if (!ft_strncmp(begin->key, key, ft_strlen(begin->key))
		&& ft_strlen(begin->key) == ft_strlen(key))
		{
			del = begin;
			tmp->next = begin->next;
			ft_lstenv_free(&del);
			return (0) ;
		}
		tmp = begin;
		begin = begin->next;
	}
	return (key);
}

char *ft_lst_get_env(t_lstenv *env, char *s)
{
	char *res;

	res = 0;
	while (env)
	{
		if (!ft_strncmp(s,env->key, ft_strlen(s))
		&& ft_strlen(env->key) == ft_strlen(s))//FIX ERROR
			res = ft_strdup(env->value); // malloc
		env = env->next;
	}
	return (res);
}

void ft_lstenv_del_all(t_lstenv **lstenv)
{
	t_lstenv *tmp;
	t_lstenv *begin;

	begin = *lstenv;
	while (begin)
	{
		tmp = begin;
		begin = begin->next;
		ft_lstenv_free(&tmp);
	}
}

void ft_get_env_key_value(char *env, char **key  , char **value)
{
	char *tmp;
	int i;

	i = 0;
	tmp = ft_strdup(env);
	if (!tmp)
		return ; //malloc
	while (tmp[i] != '=')
		i++;
	tmp[i] = '\0';
	*key =  ft_strdup(tmp);
	if (!*key[0])
		return ; //malloc
	tmp += ++i;
	*value = ft_strdup(tmp);
	if (!value[0])
		return ; //malloc
	tmp -= i;
	tmp[i] = '=';
	free(tmp);
}

t_lstenv *ft_get_lstenv(char **env)
{
	int i;
	char *key;
	char *value;
	t_lstenv *lstenv;
	t_lstenv *new;

	i = 0;
	lstenv = 0;
	while (env[i])
	{
		ft_get_env_key_value(env[i], &key, &value);
		new = ft_lstenv_new(key,value);
		ft_lstenv_add_back(&lstenv, new);
		i++;
	}
	return (lstenv);
}

char *ft_env(t_lstenv **init, char *res, char parm)
{
	static  t_lstenv *env;
	t_lstenv *begin;
	t_lstenv *new;
	char *key;
	char *value;
	if (parm == INIT)
	{
		env = *init;
		return (0);
	}
	if (parm == GET_ENV)
	    *init = env;
	if (parm == GET)
		return (ft_lst_get_env(env,res));
	if (parm == UNSET)
		return (ft_lstenv_del_key(&env, res));
	begin = env;
	if (parm == SET)
	{
		while (begin->next)
			begin = begin->next;
		ft_get_env_key_value(res, &key , &value);
		new = ft_lstenv_new(key,value); //malloc;
		begin->next = new;
	}
	if (parm == ALL)
	{
		while (begin)
		{
			write(1, begin->key, (int)ft_strlen(begin->key));
			write(1, "=", 1);
			write(1, begin->value, (int)ft_strlen(begin->value));
			write(1,"\n",1);
			begin = begin->next;
		}
		exit(0);
	}
	return (0);
}

char *ft_del_str_from_str_by_index(char *s, int start, int end)
{
	int i;
	int j;
	int len;
	char *res;

	res = 0;
	i = 0;
	j = 0;
	if (!s)
		return (0);
	len = end - start;
	if (start == end)
		len = 1;
	if (start == 0 && end == 0)
		len = 0;
	res = (char *)malloc(ft_strlen(s) - len + 1);
	if (!res)
		return (0);//malloc
	while (s[j])
	{
		if (j < start || j >= end)
			res[i++] = s[j];
		j++;
	}
	res[i] = '\0';
	return (res);
}

char *ft_strdup_to_index(char *s, int start, int end)
{
	int len;
	int i;
	char *res;

	res = 0;
	i = 0;
	if (!s)
		return (0);

	len = end - start;
	if (start == end)
		len = 1;
	if (start == 0 && end == 0)
		len = 0;
	res = (char *)malloc(len + 1);
	if (!res)
		return (0);//malloc
	while(s[start] && start < end)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

int  ft_nbrlen(long n)
{
	int i;
	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_putnbr(char *s,int *i, long nbr, char *base)
{
	if (nbr >= 10)
		ft_putnbr(s, i, nbr / 10,  base);
	s[(*i)++] = base[nbr % 10];
}

char *ft_int_to_str(int n)
{
	char *res;
	int len;
	int i;

	i = 0;
	len = ft_nbrlen(n);
	res = malloc(len + 1); //malloc
	ft_putnbr(res, &i, n,"0123456789");
	res[len] = '\0';
	return (res);
}

char *ft_del_env_to_str(char **s, int i)
{
	char *value;
	char *tmp;
	int j;
	int get_err;

	get_err = 0;
	j = i + 1;
	if (s[0][j] == '?')
		get_err = j++;
	else
		while (ft_isalpha(s[0][j]) || ft_isdigit(s[0][j]))
			j++;
	value = ft_strdup_to_index(*s,i + 1,j);
	tmp = value;
	if (get_err)
		value = ft_int_to_str(ft_errno(0,GET));
	else
		value = ft_env(0, value, GET);
	tmp = ft_free(tmp);
	tmp = *s;
	*s = ft_del_str_from_str_by_index(*s, i, j);
	tmp = ft_free(tmp);
	return (value);
}

char *ft_strjoin_index(char *s1, char *s2, int *start)
{
	char *res;
	int i;
	int j;
	int len;
	int k;

	k = 0;
	i = 0;
	j = 0;
	if (!s1)
		return (0);
	if (!s2)
	{
		res = ft_strdup(s1);
		if (!res)
			return 0;// fail malloc;
		return (res);
	}
	len = (int)(ft_strlen(s1) + ft_strlen(s2));
	res = (char *)malloc(len + 1);
	if (!res)
		return (0); // malloc
	while (i < len)
	{
		while (k < (int)ft_strlen(s2) &&  i >= *start)
			res[i++] = s2[k++];
		if (i >= len)
			break;
		res[i++] = s1[j++];
	}
	res[i] = '\0';
	return (res);
}


void ft_insert_env_to_args(char **s)
{
	int i;
	char *value;
	char *tmp;
	t_spec_chr spec;
	char debug;
	ft_init_spec(&spec);
	i = 0;
	while (s[0][i])
	{
		debug = s[0][i];
		ft_switch_quotes(&spec.quote, &spec.quotes, spec.slash, s[0][i]);
		if (s[0][i] == '$' && !spec.quote && !spec.slash)
		{
			value = ft_del_env_to_str(s, i);

			if (value)
			{
				tmp = *s;
				*s = ft_strjoin_index(*s,value,&i);
				tmp = ft_free(tmp);
				value = ft_free(value);
			}
			continue ;
		}

		ft_switch_slash(&spec, s[0][i]);
		i++;
	}
}

char *ft_get_args_val(char *line, int start, int end)
{
	char *res;

	res = ft_strdup_to_index(line,start,end);
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
	char debug;
	ft_init_spec(&spec);
	i = 0;
	count = 1;
	while (line[i])
	{
		debug = line[i];

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
		ft_switch_slash(&spec,line[i]);
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
	char debug;
	res = 0;
	ft_init_spec(&spec);
	start = *i;
	while (line[*i])
	{
		debug = line[*i];
		ft_switch_quotes(&spec.quote, &spec.quotes, spec.slash,line[*i]);
		if (!line[*i + 1])
			(*i)++;
		if ((line[*i] == ' ' && !ft_check_spec(&spec)) || !line[*i])
			{
				end = *i;
				if (!line[*i] && (*i - 1) > 0 && line[*i - 1] == ' ')
					end--;
				while (line[*i] == ' ')
					(*i)++;
				res = ft_get_args_val(line, start, end);
				break;
			}
		ft_switch_slash(&spec, line[*i]);
		(*i)++;
	}
	return (res);
}

int ft_get_token_end(int token, int *i,char *line)
{
	int res;

	res = *i + 1;
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
	if (!line)
		return (0);
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
	char debug = 0;

	*token  = -1;
	ft_init_spec(&spec);
	if (!line[*i])
		return ;
	while (line[*i] == ' ')
		(*i)++;
	start = *i;
	while (line[*i])
	{
		debug = line[*i];
		ft_switch_quotes(&spec.quote, &spec.quotes, spec.slash, line[*i]);
		*token = ft_istoken(line,i,ft_check_spec(&spec));
		if ( 0 <= *token  || !line[*i + 1])
			{
				end = ft_get_token_end(*token,i,line);
				*res = ft_strdup_to_index(line,start,end);
				return ;
			}
		ft_switch_slash(&spec,line[*i]);
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
	*save_bin = ft_free(*save_bin);
	*bin = ft_free(*bin);
	*bin = check;
	return (ret);
}

void ft_my_bin(t_lstcmds *cmds)
{
    t_lstenv  *envs;
    ft_env(&envs,0,GET_ENV);
 	if (!ft_strncmp(cmds->args[0],"unset", 6)
 	|| !ft_strncmp(cmds->args[0],"UNSET", 6))
 		ft_errno(ft_unset(cmds->args), SET);
 	if (!ft_strncmp(cmds->args[0],"env", 4)
		|| ft_strncmp(cmds->args[0],"ENV", 4))
		ft_errno(ft_export(cmds->args), SET);
    if (!ft_strncmp(cmds->args[0],"cd", 3)
        || !ft_strncmp(cmds->args[0],"CD", 3))
      ft_cd(cmds->args);
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
			check = ft_free(check);
		else
			return (ft_free_bin(&save_bin,bin,check,ret));
		check = save_bin;
		i++;
	}
	save_bin = ft_free(save_bin);
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
	if (ft_is_no_fork(cmds->args[0]))
		return (cmds->error = 2);
	if (!ft_strncmp("env",cmds->args[0], 4)
	&& ft_strlen(cmds->args[0]) == 3)
		return (cmds->error = 3);
    if (!ft_strncmp("pwd",cmds->args[0], 4)
        && ft_strlen(cmds->args[0]) == 3)
        return (cmds->error = 3);
    if (!ft_strncmp("echo",cmds->args[0], 5)
        && ft_strlen(cmds->args[0]) == 3)
        return (cmds->error = 3);
	if (!ft_strncmp("./", cmds->args[0],3)
		|| ft_strchr(cmds->args[0],'/'))
		return (ft_check_run(cmds->args[0], cmds));
	cmds->error  = ft_check_bins(&cmds->args[0],bins);
	return (0);
}

int ft_count_mass(char **mas)
{
	int i;

	i = 0;
	if (!mas)
		return (0);
	while (mas[i])
		i++;
	return (i);
}

void ft_is_error_syntax(t_lstcmds *cmds)
{
	t_lstcmds *prev;
	t_lstcmds *next;
	char **tmp;
	int i;
	prev = cmds->prev;
	next = cmds->next;

	if (!cmds->args &&
	(cmds->token == TOKEN_R_D_OUT || cmds->token == TOKEN_R_OUT)
	&& ((prev && prev->token == 1) || !prev) && next && next->args)
	{
		i = 1;
		tmp = next->args;
		cmds->args = ft_get_mas(ft_count_mass(tmp) - 1);
		while (tmp[i])
		{
			cmds->args[i - 1] = tmp[i];
			i++;
		}
		cmds->args[i - 1] = 0;
		next->args = ft_get_mas(1);
		next->args[0] = tmp[0];
		next->args[1] = 0;

	}
	else if (!cmds->args)
		cmds->error = ERR_SYNTAX_ER;
}

void ft_check_r_out(t_lstcmds *cmds)
{
	t_lstcmds *next;
	char **tmp;
	t_lstcmds *swap;
	while (cmds)
	{
		next = cmds->next;
		if (next && (cmds->token == TOKEN_R_D_OUT || cmds->token == TOKEN_R_OUT)
			&& (next->token == TOKEN_R_D_OUT || next->token == TOKEN_R_OUT))
		{
			cmds = cmds->next;
			swap = cmds;
			while (cmds)
			{
				if (cmds->token != TOKEN_R_D_OUT && cmds->token != TOKEN_R_OUT)
					break;
				cmds = cmds->next;
			}
			if (!cmds)
				return;
			tmp = cmds->args;
			cmds->args = swap->args;
			swap->args = tmp;
		}
		cmds = cmds->next;
	}
}

int   ft_check(t_lstcmds *cmds,char **env)
{
	char **bins;
	t_lstcmds *begin;

	begin = cmds;
	bins = ft_get_path(env);
	if (!bins)
		return (0); //fatal_exit;
	while (begin)
	{
		ft_is_error_syntax(begin);
		if (begin->args && begin->args[0])
			ft_get_bin(begin,bins);
		begin = begin->next;
	}
	ft_check_r_out(cmds);
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
		tmp = ft_free(tmp);
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
	tmp = ft_free(tmp);
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
		return (1);
	}
	if (S_IWUSR == (sb.st_mode & S_IFMT))
	{
		write(2, MSG_ERR_NO_PERM, ft_strlen(MSG_ERR_NO_PERM));
		write(2, s, ft_strlen(s));
		write(2,"\n",1);
		return (1);
	}
	(void)token;
	return (0);
}

int ft_run_r_out(int pipefd,char *filename,char **args,int token)
{
	int fd;
	int count;
	char *data;
	int i;
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
	if (0 >= write(fd,data,count))
		return (-1); //бяки
	i = 1;
	i = 1;
	while (args[i])
	{
		if (ft_strlen(data))
			if (0 >= write(fd," ", 1))
				return (-1); // ааа враки
		if (0 >= write(fd,args[i], ft_strlen(args[i])))
			return (-1); // ааа враки
		i++;
	}
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

int	ft_pwd(void)
{
    char *pwd;

    pwd = malloc(4096);
    if (!pwd)
        return (-1); // malloc
    if (getcwd(pwd, 4096))
    {
        ft_putendl_fd(pwd, 1); // ошибка врайта
        pwd = ft_free(pwd);
        exit(0);
    }
    else
    {
        pwd = ft_free(pwd);
        exit(1);
    }
}

void	ft_echo(char **argv)
{
    int i;
    int flag;
    int argc;
    i = 1;
    flag = 0;
    argc = ft_count_mass(argv);
    if (argc > 1) //ошибка и защиты проверить
    {
        if (!ft_strncmp(argv[i], "-n",3) && ft_strlen((argv[i])) == 2)
            flag = 1;
        i++;
        while (argv[i])
        {
            ft_putendl_fd(argv[i], 1);
            if (argv[i+1] && argv[i][0] != '\0')
                write(1," ", 1);
            i++;
        }
    }
    if (flag == 0)
        write(1, "\n", 1);
   exit(0);
}

void ft_fork_command(t_lstcmds *cmd, t_lstcmds *cmds,t_lstcmds *prev,char **env)
{
	pid_t  pid;
	int status;
	pid = fork();
	if (!pid)
	{
		ft_dup2(cmds,prev);
		if (!ft_strncmp(cmds->args[0], "env", 4))
			ft_env(0,0,ALL);
        else if (!ft_strncmp(cmds->args[0], "pwd", 4))
            ft_pwd();
        else if (!ft_strncmp(cmds->args[0], "echo",5))
            ft_echo(cmds->args);
        else
		execve(cmd->args[0],cmd->args,env);
		exit(0);
	}
	waitpid(pid,&status,0);
	cmds->status = status;
	if (status > 0)
	ft_errno(1,SET);
	else if (status == 0)
		ft_errno(0,SET);
	//printf("status = %d\n",status);
}

int ft_is_fork(t_lstcmds *cmds)
{
	t_lstcmds *prev;
	prev = cmds->prev;
	if (cmds->error == 2)
		return (3);
	if (cmds->token == TOKEN_R_IN || cmds->error < 0)
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
		 || prev->token == TOKEN_R_OUT
		 || prev->token == TOKEN_R_D_OUT
		 || prev->token == TOKEN_R_IN)
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
			ft_run_error(cmds);
		prev = cmds->prev;
		ft_open_pipe(cmds,prev);
		if (ft_is_fork(cmds) == 1)
			ft_fork_command(cmds,cmds,prev,env);
		else if (ft_is_fork(cmds) == 2)
		{
			ft_run_r_in(cmds,prev);
			ft_fork_command(prev, cmds, prev, env);
		}
		else if (ft_is_fork(cmds) == 3)
			ft_my_bin(cmds);
		if (ft_is_r_out(prev))
			ft_run_r_out(prev->fds[0],cmds->args[0], cmds->args, prev->token);
		ft_close_pipe(cmds,prev);
		cmds = cmds->next;
	}
}

# include <limits.h>
# include <errno.h>
# define ERROR 1
# define SUCCESS 0
# define STDERR 2
# define BUFF_SIZE 4096
# include <string.h>

static void		print_error(char **args)
{
    ft_putstr_fd("cd: ", 2);
    if (args[2])
        ft_putstr_fd("string not in pwd: ", 2);
    else
    {
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putendl_fd(args[1], 2);
}

//static char		*get_env_path(t_lstenv *env, const char *var, size_t len)
//{
//    char	*oldpwd;
//    int		i;
//    int		j;
//    int		s_alloc;
//
//    while (env && env->next != NULL)
//    {
//  //      printf("%s\n",var);
//   //     printf("%zu\n",len);
//        if (ft_strncmp(env->value, var, len) == 0)
//        {
//      //      write(1,"kdkdk\n",6);
//        //    printf("%s\n",env->key);
//            s_alloc = ft_strlen(env->value)- len;
//     //       printf("%d\n",s_alloc);
//            if (!(oldpwd = malloc(sizeof(char) * s_alloc + 1)))
//                return (NULL);
//            i = 0;
//            j = 0;
//        //    write(1,"kdkdk\n",6);
//            while (env->value[i++])
//            {
//                if (i > (int)len)
//                    oldpwd[j++] = env->value[i];
//            }
//            i = 0;
//            printf("%s\n",oldpwd);
//            while (env->value[i++])
//            {
//                if (i > (int)len)
//                    oldpwd[j++] = env->value[i];
//            }
//            oldpwd[j] = '\0';
//            printf("%s\n",oldpwd);
//            return (oldpwd);
//        }
//        env = env->next;
//    }
//    return (NULL);
//}

int			env_add(const char *value, t_lstenv *env)
{
    t_lstenv	*new;
    t_lstenv	*tmp;

    if (env && env->value == NULL)
    {
        env->value = ft_strdup(value);
        return (SUCCESS);
    }
    if (!(new = malloc(sizeof(t_lstenv))))
        return (-1);
    new->value = ft_strdup(value);
    while (env && env->next)
        env = env->next;
    tmp = env->next;
    env->next = new;
    new->next = tmp;
    return (SUCCESS);
}

char		*get_env_name(char *dest, const char *src)
{
    int		i;

    i = 0;
    while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}
int			is_in_env(t_lstenv *env, char *args)
{
    char	var_name[BUFF_SIZE];
    char	env_name[BUFF_SIZE];

    get_env_name(var_name, args);
    while (env && env->next)
    {
        get_env_name(env_name, env->value);
        if (!ft_strncmp(var_name, env_name, ft_strlen(env_name)) && ft_strlen((var_name)) == ft_strlen(env_name))
        {
            env->value = ft_free(env->value);
            env->value = ft_strdup(args);
            return (1);
        }
        env = env->next;
    }
    return (SUCCESS);
}

static int		update_oldpwd(void)
{
    char	cwd[PATH_MAX];
    char	*oldpwd;

    if (getcwd(cwd, PATH_MAX) == NULL)
        return (ERROR);
    if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
        return (ERROR);
    ft_env(0,oldpwd,SET);
	oldpwd = ft_free(oldpwd);
    return (SUCCESS);
}

static int		go_to_path(int option)
{
    int		ret;
    char	*env_path;

    env_path = NULL;
    if (option == 0)
    {
        update_oldpwd();
        env_path = ft_env(0,"HOME", GET);// Путь
                //get_env_path(env, "HOME", 4);
        if (!env_path)
            ft_putendl_fd("minishell : cd: HOME not set", STDERR);
        if (!env_path)
            return (ERROR);
    }
    else if (option == 1)
    {
        env_path = ft_env(0,"HOME", GET);//Путь
                //get_env_path(env, "OLDPWD", 6);
        if (!env_path)
            ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR);
        if (!env_path)
            return (ERROR);
        update_oldpwd();
    }
    ret = chdir(env_path);
    env_path = ft_free(env_path);
    return (ret);
}

int				ft_cd(char **args)
{
    int		cd_ret;

    if (!args[1])
        return (go_to_path(0));
    if (!ft_strncmp(args[1], "-",1) && ft_strlen((args[1])) == 1)
        cd_ret = go_to_path(1);
    else
    {
        update_oldpwd();
        cd_ret = chdir(args[1]);
        if (cd_ret < 0)
            cd_ret *= -1;
        if (cd_ret != 0)
            print_error(args);
    }
    return (cd_ret);
}

int ft_is_env_key(char *key)
{
	int i;
	i = 0;
	while (key[i])
		if (ft_isdigit(key[i]) || ft_isalpha(key[i]) || key[i] == '_')
			i++;
		else
			return (0);

	return (1);
}

void ft_parse(char **line,char **env)
{
	t_lstcmds *cmds;
	char *str_token;
	int token;
	int i;
	token = -1;
	cmds = 0;
	i = 0;
	//(void)env;

	while (line[0][i])
	{
		ft_get_token(*line, &i, &str_token, &token);
		if (!str_token)
			str_token = ft_strdup("");
		ft_insert_env_to_args(&str_token);
		ft_lstcmdsadd_back(&cmds,ft_lstcmdsnew(ft_get_args(str_token),
		token));
        ft_check(cmds,env);
		str_token = ft_free(str_token);
	}

//	t_lstcmds *begin;
//	begin = cmds;
//	int j;
//	j = 0;
//	while (begin)
//	{
//		printf("token = %d error = %d || ",begin->token,begin->error);
//		if(begin->args)
//		while (begin->args[j])
//		{
//			printf("%s|", begin->args[j]);
//			j++;
//		}
//		j = 0;
//		printf("\n");
//		begin = begin->next;
//	}
        ft_run_command(cmds,env);
        ft_lstcmdsdel(&cmds);
}

int ft_is_export(char *s)
{
	int i;
	int equal;
	i = 0;
	equal = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			equal = 1;
			break;
		}
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_')
			return (-1);
		i++;
	}
	if (equal == 0)
		return (0);
	if (s[0] == '=')
		return (-1);
	return (1);
}

int ft_export(char *args[])
{
	int i;
	int ret;
	int check;
	ret = 0;
	i = 1;
	while (args[i])
	{
		check = ft_is_export(args[i]);
		if (check < 0)
		{
			ret = 1;
			ft_put_error(args[i]);
			ft_put_error(" ОШИБКА\n");
		}
		if (check == 1)
			ft_env(0,args[i],SET);
		i++;
	}
	return (ret);
}

int main(int argc,char *argv[],char *env[])
{
	(void)argc;
	(void)argv;
	char byte;
	char buf[2];
	char *command;
	char *tmp;
	t_lstenv *lstenv;
	lstenv = ft_get_lstenv(env);
	ft_env(&lstenv, 0,INIT);

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

			ft_parse(&command, env);
			command = ft_free(command);
			write(0,"> ",2);
		}
		else
		{
			tmp = command;
			command = ft_strjoin(command,buf);
			tmp = ft_free(tmp);
		}
	}
}



