/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:41:58 by weambros          #+#    #+#             */
/*   Updated: 2021/03/31 14:49:14 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h> // удалить
# include "../libs/libft/libft.h"
# include <sys/stat.h>
# include <fcntl.h>
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#define	TOKEN_BIN 1
#define TOKEN_PIPE 2
#define TOKEN_R_IN 3
#define TOKEN_R_OUT 4
#define TOKEN_R_D_OUT 5
#define TOKEN_ANDAND 6
#define TOKEN_OROR	7


typedef struct	s_spec_chr
{
	int quote;
	int quotes;
	int slash;
}				t_spec_chr;

typedef struct	s_lstcmds
{
	char	**args;
	int 	error;
	int		token;
	int		status;
	int		fds[2];
	void	*prev;
	void	*next;
}				t_lstcmds;



void ft_switch_quotes(int *quote,int *quotes,int slash, char c);
int ft_count_tokens(char *line);
void ft_init_spec(t_spec_chr *spec);

#endif