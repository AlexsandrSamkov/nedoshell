#include "minishell.h"

char  **ft_parse_bin(char **envv)
{
	char *tmp;
	int i;
	i = 0;

	while(envv[i])
	{
		if (!ft_strncmp(envv[i],"PATH=",5))
			break;
		i++;
	}
	tmp = envv[i];
	tmp += 5;
	return (ft_split(tmp,':'));
}

int ft_parse(char **line)
{
	if (!ft_strncmp(*line,"cd",2) && (ft_isspace(*line[2]) || !*line[2]))
		write(1,"is cd",5);
	else if (!ft_strncmp(*line,"pwd",3)
	&& (ft_isspace(*line[3]) || !*line[3]))
		write(1,"is pwd",6);
	else if (!ft_strncmp(*line,"env",3)
	&& (ft_isspace(*line[3]) || !*line[3]))
		write(1,"is env",6);
	else if (!ft_strncmp(*line,"exit",4)
	&& (ft_isspace(*line[4]) || !*line[4]))
		write(1,"is exit",7);
	if (!ft_strncmp(*line,"unset",5)
	&& (ft_isspace(*line[5]) || !*line[5]))
		write(1,"is unset",8);
	if (!ft_strncmp(*line,"export",6)
	&& (ft_isspace(*line[6]) || !*line[6]))
		write(1,"is export",9);
	return (0);
}

char *ft_get_env(char **envv, char *val)
{
	char *res;
	char *tmp;
	int i;
	size_t len;

	if(!val || !envv)
		return (0);
	i = -1;
	res = 0;
	len = ft_strlen(val);
	tmp = 0;
	while (envv[++i])
		if(!ft_strncmp(envv[i],val,len))
		{
			tmp = envv[i];
			tmp += len + 1;
			res = ft_strdup(tmp);
			break;
		}
	return (res);
}