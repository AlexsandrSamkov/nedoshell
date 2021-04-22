/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:40:10 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/16 20:11:49 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	add_to_hist(char *cmd)
{
	t_history	*hist;
	t_data		*new;
	t_data		*tmp;

	hist = NULL;
	hist = save_hist(&hist);
	if (ft_strlen(cmd) == 0 || !hist)
	{
		free(cmd);
		return ;
	}
	new = (t_data *)malloc(sizeof(t_data));
	if (new == NULL)
		return ;
	new->data = cmd;
	tmp = hist->hist_list;
	hist->hist_list = new;
	new->next = tmp;
	hist->count++;
}

t_history	*save_hist(t_history **hist)
{
	static t_history	*tmp;

	if (*hist == NULL)
		return (tmp);
	tmp = *hist;
	return (*hist);
}

void	fill_histfile(void)
{
	t_history	*hist;
	int			fd;

	hist = NULL;
	hist = save_hist(&hist);
	if (!hist)
		return ;
	fd = open(HISTORY_FILE_PATH, O_FILL, S_IWUSR | S_IRUSR);
	if (fd < 0)
		return ;
	write_backword(fd, hist->hist_list);
	close(fd);
}

void	free_history(void)
{
	t_history	*hist;
	t_data		*to_free;

	hist = NULL;
	hist = save_hist(&hist);
	if (!hist)
		return ;
	fill_histfile();
	while (hist->hist_list)
	{
		to_free = hist->hist_list;
		hist->hist_list = hist->hist_list->next;
		free(to_free->data);
		free(to_free);
	}
	if (hist->tmp)
		free(hist->tmp);
	free(hist);
}

void	write_backword(int fd, t_data *list)
{
	if (!list)
		return ;
	write_backword(fd, list->next);
	ft_putendl_fd(list->data, fd);
}
