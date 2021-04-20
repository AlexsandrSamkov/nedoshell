/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:41:58 by weambros          #+#    #+#             */
/*   Updated: 2021/04/20 06:01:52 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h> // удалит
# include "../libs/libft/libft.h"
# include <sys/stat.h>
# include <fcntl.h>

# include <limits.h>
# include <errno.h>
# define ERROR 1
# define SUCCESS 0
# define STDERR 2
# include <string.h>

# define MSG_ERR_NO_FILE ": No such file or directory\n"
# define MSG_ERR_NO_PERM ": Permission denied\n"
# define MSG_ERR_IS_DIRECT ": is a directory\n"
# define MSG_ERR_N0_COMMAND "Command not found: "
# define MSG_ERR_SYNTAX_ERR "syntax error near unexpected token\n"
# define MSG_ERR_NOT_VALID_ID "\': not a valid identifier"
# define MSG_ERR_UNSET "unset: `"
# define MSG_ERR_NO_MALLOC "Fatal error: no malloc"
# define MSG_ERR_NO_WRITE "Fatal error: no write"
# define MSG_ERR_NO_PIPE "Fatal error: no open pipe"
# define MSG_ERR_FILE_NAME_ARGS \
"filename argument required\n.: usage: .filename [arguments]\n"

# define SET 'C'
# define GET 'G'
# define INIT 'I'
# define UNSET 'U'
# define ALL 'A'
# define GET_ENV 'E'

# define ERR_NO_FILE -1
# define ERR_NO_PERM -2
# define ERR_IS_DIRECT -3
# define ERR_N0_COMMAND -4
# define ERR_SYNTAX_ER -5
# define ERR_FILE_NAME_ARGS -6

# define TOKEN_BIN 1
# define TOKEN_PIPE 2
# define TOKEN_R_IN 3
# define TOKEN_R_OUT 4
# define TOKEN_R_D_OUT 5
# define TOKEN_ANDAND 6
# define TOKEN_OROR	7

pid_t		g_pid;

typedef struct s_spec_chr
{
	int	quote;
	int	quotes;
	int	slash;
}				t_spec_chr;

typedef struct s_lstcmds
{
	char	**args;
	int		error;
	int		token;
	int		fds[2];
	void	*prev;
	void	*next;
}				t_lstcmds;

typedef struct s_lstenv
{
	char	*key;
	char	*value;
	void	*next;
}				t_lstenv;

char		**ft_get_env_mass(void);
char		**ft_get_mas(int count);
int			ft_is_no_fork(char *s);
int			ft_unset(char **args);
void		ft_put_error(char *s);
int			ft_errno(int n, char f);
void		ft_check_str_fatal(char *str);
void		*ft_free(void *s);
void		ft_free_mas(char ***mas);
int			ft_switch_quotes(int *quote, int *quotes, int slash, char c);
t_lstcmds	*ft_lstcmdslast(t_lstcmds *lst);
void		ft_lstcmdsadd_back(t_lstcmds **lst, t_lstcmds *new);
t_lstcmds	*ft_lstcmdsnew(char **args, int token);
void		ft_lstcmdsdel(t_lstcmds **cmds);
int			ft_switch_slash(t_spec_chr *spec, char c);
int			ft_istoken(char *s, int *i, int spec);
t_spec_chr	*ft_init_spec(void);
int			ft_check_spec(t_spec_chr *spec);
int			ft_count_args_spec(char *s);
void		ft_del_spec(char **s);
t_lstenv	*ft_lstenv_new(char *key, char *value);
t_lstenv	*ft_lstenv_last(t_lstenv *lstenv);
void		ft_lstenv_add_back(t_lstenv **lstenv, t_lstenv *new);
void		ft_lstenv_free(t_lstenv **del);
char		*ft_lstenv_del_key(t_lstenv **env, char *key);
char		*ft_lst_get_env(t_lstenv *env, char *s);
void		ft_lstenv_del_all(t_lstenv **lstenv);
void		ft_get_env_key_value(char *env, char **key, char **value);
t_lstenv	*ft_get_lstenv(char **env);
char		*ft_env(t_lstenv **init, char *res, char parm);
char		*ft_del_str_from_str_by_index(char *s, int start, int end);
char		*ft_strdup_to_index(char *s, int start, int end);
int			ft_nbrlen(long n);
void		ft_putnbr(char *s, int *i, long nbr, char *base);
char		*ft_int_to_str(int n);
char		*ft_del_env_to_str(char **s, int i);
char		*ft_strjoin_index(char *s1, char *s2, int *start);
void		ft_insert_env_to_args(char **s);
char		*ft_get_args_val(char *line, int start, int end);
int			ft_args_count(char *line);
char		*ft_get_args_str(char *line, int *i);
int			ft_get_token_end(int token, int *i, char *line, int start);
char		**ft_get_args(char *line);
void		ft_get_token(char *line, int *i, char **res, int *token);
char		**ft_get_path(t_lstenv *env);
int			ft_free_bin(char **save_bin, char **bin, char *check, int ret);
void		ft_my_bin(t_lstcmds *cmds);
int			ft_check_run(char *s, t_lstcmds *cmds);
int			ft_check_bin(char *s);
int			ft_check_bins(char **bin, char **bins);
int			ft_get_bin(t_lstcmds *cmds, char **bins);
int			ft_count_mass(char **mas);
void		ft_is_error_syntax(t_lstcmds *cmds);
void		ft_check_r_out(t_lstcmds *cmds);
int			ft_check(t_lstcmds *cmds);
int			ft_get_pipe_data(int fd, char **data);
void		ft_strjoin_and_free(char **s1, char *s2);
char		*ft_run_r_in(t_lstcmds *cmds, t_lstcmds *prev);
int			ft_check_open_r_error(char *s, int token);
int			ft_run_r_out(int pipefd, char *filename, char **args, int token);
int			ft_pwd(void);
int 		ft_echo(char **argv);
void		ft_fork_command(t_lstcmds *cmd, t_lstcmds *cmds, t_lstcmds *prev);
int			ft_is_fork(t_lstcmds *cmds);
void		ft_open_pipe(t_lstcmds *cmds, t_lstcmds *prev);
void		ft_close_pipe(t_lstcmds *cmds, t_lstcmds *prev);
int			ft_is_r_out(t_lstcmds *prev);
int			ft_check_error_syntax(t_lstcmds *cmds);
int			ft_run_error(t_lstcmds *cmds);
void		ft_run_command(t_lstcmds *cmds);
int			ft_cd(char **args);
int			ft_is_env_key(char *key);
void		ft_parse(char **line);
int			ft_is_export(char *s);
int			ft_export(char *args[]);
char		*ft_get_token_data(int token, int start, char *line, int *i);
void		ft_exit_fatal(char *s);
void		ft_env_put_all(t_lstenv *env);
int			ft_return_and_free(void *s, int ret);
void		ft_env_set(t_lstenv *env, char *set);
int			ft_if_del_spec(char *s, int j, t_spec_chr *spec);
void		ft_swap_in_token_args(t_lstcmds *cmds, t_lstcmds *next);
int			ft_cmds_swap_r_out(t_lstcmds **cmds);
void		ft_wait_command(void);
void		ft_exit(void);
char		*ft_strdup_token(char *s, int start, int end);
void		ft_run_command2(t_lstcmds *cmds);
int	ft_run_bin(t_lstcmds *cmds, int is_exit);



#endif