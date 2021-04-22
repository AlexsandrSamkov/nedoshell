/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:41:58 by weambros          #+#    #+#             */
/*   Updated: 2021/04/22 08:47:32 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <limits.h>
# include <stdio.h>

# define ERROR 1
# define SUCCESS 0
# define STDERR 2

# define MSG_ERR_NO_FILE ": No such file or directory\n"
# define MSG_ERR_NO_PERM ": Permission denied\n"
# define MSG_ERR_NO_PERM_F ": Permission denied\n"
# define MSG_ERR_IS_DIRECT ": is a directory"
# define MSG_ERR_N0_COMMAND "Command not found: "
# define MSG_ERR_SYNTAX_ERR "syntax error near unexpected token\n"
# define MSG_ERR_NOT_VALID_ID "\': not a valid identifier"
# define MSG_ERR_UNSET "unset: `"
# define MSG_ERR_NO_MALLOC "Fatal error: no malloc"
# define MSG_ERR_NO_WRITE "Fatal error: no write"
# define MSG_ERR_NO_PIPE "Fatal error: no open pipe"
# define MSG_ERR_NO_FORK "Fatal error: no open fork"
# define MSG_ERR_NO_OPEN "Fatal error: no open flow"
# define MSG_ERR_FILE_NAME_ARGS	\
"filename argument required\n.: usage: .filename [arguments]\n"

# define SET 'C'
# define GET 'G'
# define INIT 'I'
# define UNSET 'U'
# define ALL 'A'
# define GET_ENV 'E'
# define DEL 'D'

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

# define BUFF_SIZE 1000000
# define LEFT_K 4479771
# define TOP_K 4283163
# define RIGHT_K 4414235
# define BOTTOM_K 4348699
# define UP_K 2117425947
# define DOWN_K 2117491483
# define BACK_K 127
# define HOME_K 4741915
# define END_K 4610843
# define INTER_K 10
# define CTL_D 4
# define SO (tgetstr("so", NULL))
# define SE (tgetstr("se", NULL))
# define CM (tgetstr("cm", NULL))
# define CD (tgetstr("cd", NULL))
# define DO (tgetstr("do", NULL))


# define HISTORY_FILE_PATH "/tmp/.21sh_history"
# define O_FILL (O_CREAT | O_WRONLY | O_TRUNC)

# define READ_SIZE 4096

pid_t		gl_pid;

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

typedef struct		s_cmdline
{
	int				cur;
	int				len;
	int				key;
	int				b_p;
	int				is_s;
	int				s_sp;
	int				res;
	int				h_p;
	int				ctl_d;
	int				ctl_c;
	struct winsize	w;
	struct s_kursor	*init_p;
	struct s_kursor	*cur_p;
	char			chars[BUFF_SIZE];
	char			prompt[PATH_MAX];
}					t_cmdline;

typedef struct		s_buttons
{
	long			key;
	void			(*f)(t_cmdline *l);
}					t_buttons;

typedef struct		s_kursor
{
	int				r;
	int				c;
}					t_kursor;

typedef struct		s_data
{
	char			*data;
	struct s_data	*next;
}					t_data;

typedef	struct		s_history
{
	struct s_data	*hist_list;
	char			*tmp;
	int				count;
}					t_history;


void	print_error(char **args);
int	update_oldpwd(void);
int	go_to_path(int option);
int	ft_cd(char **args);
void	ft_check_r_out2(t_lstcmds *cmds, int j, char ***args);
void	ft_check_r_out(t_lstcmds *cmds);
void	ft_is_error_syntax(t_lstcmds *cmds);
int	ft_check(t_lstcmds *cmds);
int	ft_if_del_spec(char *s, int j, t_spec_chr *spec);
void	ft_del_spec(char **s);
char	*ft_env(t_lstenv **init, char *res, char parm);
int	ft_unset(char **args);
t_lstenv	*ft_get_lstenv(char **env);
char 	**ft_get_env_mass_value(t_lstenv *env, char **res);
char	**ft_get_env_mass(void);
char	*ft_lst_get_env(t_lstenv *env, char *s);
void	ft_env_put_all(t_lstenv *env);
void	ft_get_env_key_value(char *env, char **key, char **value);
int	ft_env_set_2(t_lstenv *env, t_lstenv *next, char *key, char *value);
void	ft_env_set(t_lstenv *env, char *set);
char	*ft_lstenv_del_key(t_lstenv **env, char *key);
int	ft_is_env_key(char *key);
int	ft_is_export(char *s);
int	ft_export(char *args[]);
char	*ft_del_env_to_str(char **s, int i);
void	ft_exit_fatal(char *s);
void	ft_put_error(char *s);
int	ft_errno(int n, char f);
void	ft_check_str_fatal(char *str);
int	ft_check_error_syntax(t_lstcmds *cmds);
int	ft_run_error_2(t_lstcmds *cmds);
int	ft_run_error(t_lstcmds *cmds);
t_lstcmds	*ft_is_run_pipe(t_lstcmds *cmds);
void	ft_pipe(t_lstcmds *cmds, t_lstcmds *prev);
void	ft_dup2(t_lstcmds *cmds, t_lstcmds *prev);
void	ft_run_pipe2(t_lstcmds **cmd, char **env);
void	ft_run_pipe(t_lstcmds *cmds, char **env);
void	*ft_free(void *s);
void	ft_free_mas(char ***mas);
int	ft_return_and_free(void *s, int ret);
void	ft_strjoin_and_free(char **s1, char *s2);
char	*ft_get_args_val(char *line, int start, int end);
char	*ft_get_args_str(char *line, int *i);
int	ft_args_count(char *line);
char	**ft_get_args(char *line);
char	**ft_get_path(t_lstenv *env);
int	ft_free_bin(char **save_bin, char **bin, char *check, int ret);
void	ft_my_bin(t_lstcmds *cmds);
int	ft_check_bin(char *s);
char	*ft_strdup_token(char *s, int start, int end);
int	ft_check_run_2(struct stat sb, t_lstcmds *cmds);
int	ft_check_run(char *s, t_lstcmds *cmds);
int	ft_get_bin(t_lstcmds *cmds, char **bins);
int	ft_check_bins(char **bin, char **bins);
void	ft_insert_env_to_args(char **s);
t_lstcmds	*ft_lstcmdslast(t_lstcmds *lst);
void	ft_lstcmdsadd_back(t_lstcmds **lst, t_lstcmds *new);
t_lstcmds	*ft_lstcmdsnew(char **args, int token);
void	ft_lstcmdsdel(t_lstcmds **cmds);
t_lstenv	*ft_lstenv_new(char *key, char *value);
t_lstenv	*ft_lstenv_last(t_lstenv *lstenv);
void	ft_lstenv_add_back(t_lstenv **lstenv, t_lstenv *new);
void	ft_lstenv_free(t_lstenv **del);
void	ft_lstenv_del_all(t_lstenv **lstenv);
int	ft_pwd(void);
int	ft_echo(char **argv);
void	ft_exit(void);
void	ft_check_open_r_error2(char *s, struct stat sb, int token, int *ret);
int	ft_check_open_r_error(char *s, int token);
void	ft_run_r(t_lstcmds *cmds, t_lstcmds *prev);
void	ft_run_r_in2(t_lstcmds *cmds, char *buf, int *ret);
void	ft_run_r_in(t_lstcmds *cmds);
void	ft_run_or_and(t_lstcmds **cmd);
void	ft_parse(char *line);
int	ft_is_no_fork(char *s);
void	ft_run_excve(t_lstcmds *cmds, char **env);
void	ft_close_all_pipe(t_lstcmds *cmds);
void	ft_run(t_lstcmds *cmds, t_lstcmds *prev, char **env);
void	ft_run_command(t_lstcmds *cmds);
int	ft_run_bin2(t_lstcmds *cmds, int *ret, int *run);
int	ft_run_bin(t_lstcmds *cmds, int is_exit);
void	ft_wait(pid_t);
int	ft_count_mass(char **mas);
char	**ft_get_mas(int count);
void	ft_strjoin_index_get(char *s1, char *s2, char **res, int start);
char	*ft_strjoin_index(char *s1, char *s2, int *start);
char	*ft_int_to_str(int n);
void	ft_putnbr(char *s, int *i, long nbr, char *base);
int	ft_nbrlen(long n);
char	*ft_strdup_to_index(char *s, int start, int end);
char	*ft_del_str_from_str_by_index(char *s, int start, int end);
int	ft_check_spec(t_spec_chr *spec);
int	ft_switch_quotes(t_spec_chr *spec, char c);
int	ft_switch_slash(t_spec_chr *spec, char c);
t_spec_chr	*ft_init_spec(void);
int	ft_count_args_spec(char *s);
char	*ft_get_token_data(int token, int start, char *line, int *i);
int	ft_get_token_end(int token, int *i, char *line, int start);
void	ft_get_token(char *line, int *i, char **res, int *token);
int	ft_istoken_2(char *s, int *i);
int	ft_istoken(char *s, int *i, int spec);
void	show_prompt(t_cmdline *l);
char	*aff_prompt2(int ret, char *cmdl, char *temp);
char	*aff_prompt(t_lstenv *env);
int		check_valtok(char c);

int	check_errline2(char *str, int ret);
int	check_errline(char *str);
int	check_space(char c);
int	check_spacestr(char *str);
int	check_allerr(char *str);
int	check_aller(char *str);
int	ft_perror(char *s, char *str, int ret);
int	add_to_env(t_lstenv **env, char *name, char *value);
char	*prompt(t_lstenv *env);
int	check_redirect(char *str);
t_lstenv	*elem_env(char *name, char *value);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
void	ft_memdel(void **ap);
void	init_history(void);
void	fill_from_histfile(void);
char	*ft_strcpy(char *dest, const char *src);
void	ft_putchar(char c);
t_cmdline	*init_cmdline(char *pr);
t_cmdline	*malloc_cmd(void);
void	get_cur_pos(t_kursor *t);
void	init_cur(t_cmdline *l);
void	swap_p(t_kursor *p1, t_kursor *p2, int a);
void	plus(t_kursor *p, t_cmdline *l, t_kursor *p1, int i);
void	free_out(t_cmdline *l);
void	go_to_the_end(t_cmdline *l);
void	free_environ(t_lstenv *lst);
void	right_kursor(t_cmdline *l);
void	left_kursor(t_cmdline *l);
void	delete(t_cmdline *l);
void	down_k(t_cmdline *l);
void	up_k(t_cmdline *l);
void	end_k(t_cmdline *l);
void	home_k(t_cmdline *l);
void	return_k(t_cmdline *l);
t_cmdline	*keep_l(t_cmdline *l, int cmd);
void	read_key(t_cmdline *l);
void	sheft(t_cmdline *l);
void	add_at(t_cmdline *l);
void	match_key(t_cmdline *l);
void	add_to_hist(char *cmd);
t_history	*save_hist(t_history **hist);
void	fill_histfile(void);
void	free_history(void);
void	write_backword(int fd, t_data *list);
void	default_term_mode(void);
char	*ft_strjoin_f(char *s1, char *s2, int a, int b);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strnew(size_t size);
char	*ft_getenv(t_lstenv *env, char *name);
int	ft_strcmp(const char *s1, const char *s2);
char	*read_line2(t_cmdline *l);
char	*read_line(char *prompt);
void	init_term(void);
void	excute_key(t_buttons keys[19], t_cmdline *l);
char	*get_element_by_index(int index, t_data *list);
void	top_k(t_cmdline *l);
void	bottom_k(t_cmdline *l);
void	print_cmdline(t_cmdline *l);
t_lstenv	*creat_env(char **env);
int	check_spechar(char c);
void	ctrlc_sig(int seg);
void	ctl_d(t_cmdline *l);
int	ft_switch_token(int *switch_token, int token);
pid_t *ft_pid_mass(char c, pid_t value);
# endif






