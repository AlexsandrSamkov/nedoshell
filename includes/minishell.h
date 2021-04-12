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

# define MSG_ERR_NO_FILE "No such file or directory"
# define MSG_ERR_NO_PERM "Permission denied "
# define MSG_ERR_IS_DIRECT "Is a directory "
# define MSG_ERR_N0_COMMAND "Command not found: "
# define MSG_ERR_SYNTAX_ERR "syntax error near unexpected token\n"
# define MSG_ERR_NOT_VALID_ID "\': not a valid identifier"
# define MSG_ERR_UNSET "unset: `"

# define SET 'C'
# define GET 'G'
# define INIT 'C'
# define UNSET 'U'

# define ERR_NO_FILE -1
# define ERR_NO_PERM -2
# define ERR_IS_DIRECT -3
# define ERR_N0_COMMAND -4
# define ERR_SYNTAX_ER -5
# define ERR_GO_NEXT	-6


#define	TOKEN_BIN 1
#define TOKEN_PIPE 2
#define TOKEN_R_IN 3
#define TOKEN_R_OUT 4
#define TOKEN_R_D_OUT 5
#define TOKEN_ANDAND 6
#define TOKEN_OROR	7

#define TOKEN_STR_PIPE "|"
#define TOKEN_STR_BIN ";"
#define TOKEN_STR_R_IN "<"


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

typedef struct	s_lstenv
{
	char *key;
	char *value;
	void *next;
}				t_lstenv;


int ft_count_tokens(char *line);
void ft_init_spec(t_spec_chr *spec);

#endif