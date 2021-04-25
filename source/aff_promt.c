/* ************************************************************************** */
/*						                                                    */
/*                                                        :::      ::::::::   */
/*   aff_promt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjennett <sjennett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:40:06 by sjennett          #+#    #+#             */
/*   Updated: 2021/04/16 16:50:39 by sjennett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_prompt(t_cmdline *l)
{
	t_history			*hist;

	hist = NULL;
	hist = save_hist(&hist);
	ft_putstr_fd(l->prompt, 1);
}

char	*aff_prompt2(int ret, char *cmdl, char *temp)
{
	while (ret == 1 || ret == 2)
	{
		temp = read_line(">");
		if (temp && *temp != '\n')
		{
			if (ret == 2)
				cmdl = ft_strjoin_f(cmdl, "\n", 1, 0);
			cmdl = ft_strjoin_f(cmdl, temp, 1, 1);
			ret = check_aller(cmdl);
		}
		else if (temp && *temp == '\n')
		{
			ft_memdel((void **)&temp);
			ret = -1;
		}
		else
			ret = ft_perror(0, "syntax error: unexpected end of file", -1);
	}
	if (!check_spacestr(cmdl))
		add_to_hist(ft_strdup(cmdl));
	if (ret == -1)
		ft_memdel((void **)&cmdl);
	if (cmdl)
		return (cmdl);
	return (ft_strdup("\0"));
}

char	*aff_prompt(t_lstenv *env)
{
	int		ret;
	char	*cmdl;
	char	*temp;
	int		i;

	temp = NULL;
	cmdl = prompt(env);
	if (!(cmdl))
		return (0);
	ret = check_aller(cmdl);
	if (ret == 5)
	{
		i = 0;
		while (cmdl[i] != '#')
			i++;
		cmdl[i] ='\0';
	}
	return (aff_prompt2(ret, cmdl, temp));
}
