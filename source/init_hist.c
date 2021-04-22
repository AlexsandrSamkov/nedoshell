/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:40:15 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/16 19:55:33 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lstenv	*elem_env(char *name, char *value)
{
	t_lstenv	*elem;

	elem = (t_lstenv *)malloc(sizeof(t_lstenv));
	if (!(elem))
		return (0);
	elem->key = ft_strdup(name);
	if (!(elem->key))
		return (0);
	if (value)
	{
		elem->value = ft_strdup(value);
		if (!(elem->value))
			return (0);
	}
	if (!value)
	{
		elem->value = ft_strdup("\0");
		if (!(elem->value))
			return (0);
	}
	elem->next = 0;
	return (elem);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*t;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (unsigned char)ft_strlen(s))
		return (NULL);
	t = (char *)malloc((len + 1) * sizeof(char));
	if (!t)
		return (NULL);
	while (i++ < start)
		s++;
	i = 0;
	while (i < len && *s)
		t[i++] = *s++;
	t[i] = '\0';
	return (t);
}

void	ft_memdel(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
}

void	init_history(void)
{
	t_history	*hist;

	hist = (t_history *)malloc(sizeof(t_history));
	if ((hist) == NULL)
		exit(0);
	hist->tmp = NULL;
	hist->count = 0;
	hist->hist_list = NULL;
	save_hist(&hist);
	fill_from_histfile();
}

void	fill_from_histfile(void)
{
	int		fd;
	char	*line;

	fd = open(HISTORY_FILE_PATH, O_RDONLY);
	if (fd < 0)
		return ;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
		add_to_hist(line);
	close(fd);
}
