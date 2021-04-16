/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:53:38 by weambros          #+#    #+#             */
/*   Updated: 2021/04/14 22:09:36 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_parse(char **line)
{
	t_lstcmds *cmds;
	char *str_token;
	int token;
	int i;
	token = -1;
	cmds = 0;
	i = 0;
	int j;
	t_lstcmds *begin;

	while (line[0][i])
	{
		ft_get_token(*line, &i, &str_token, &token);
		if (!str_token)
			str_token = ft_strdup("");
//		printf("str =%s\n",str_token);
		ft_insert_env_to_args(&str_token);
		ft_lstcmdsadd_back(&cmds,ft_lstcmdsnew(ft_get_args(str_token),
											   token));
		ft_check(cmds);
		if (token == TOKEN_BIN)
		{

			begin = cmds;

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
			ft_run_command(cmds);
			ft_lstcmdsdel(&cmds);
		}
		str_token = ft_free(str_token);
	}


	begin = cmds;
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
	if (cmds)
		ft_run_command(cmds);
	ft_lstcmdsdel(&cmds);
}