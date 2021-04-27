#include "../includes/minishell.h"

void	ft_close_all_pipe(t_lstcmds *cmds)
{
	pid_t	*mass;
	int		i;

	i = 0;
	mass = ft_pid_mass(GET, 0);
	while (mass[i])
		ft_wait(mass[i++]);
	ft_pid_mass(DEL, 0);
	while (cmds)
	{
		if (cmds->fds[1] > 0)
			close(cmds->fds[1]);
		if (cmds->fds[0] > 0)
			close(cmds->fds[0]);
		cmds = cmds->prev;
	}
}

void	ft_run_pipe(t_lstcmds *cmds, char **env)
{
	t_lstcmds	*begin;
	t_lstcmds	*prev;

	begin = cmds;
	while (cmds)
	{
		prev = cmds->prev;
		ft_pipe(cmds, prev);
		if (prev && (prev->token == TOKEN_R_D_OUT \
			|| prev->token == TOKEN_R_OUT))
		{
			ft_run_r(cmds, prev);
			cmds = cmds->prev;
			continue ;
		}
		if (ft_run_error(cmds))
		{
			cmds = cmds->prev;
			continue ;
		}
		ft_run_pipe2(&cmds, env);
	}
	ft_close_all_pipe(cmds);
}

void	ft_fix_signal_quit(char *s)
{
	int	i;
	int	j;

	i = (int) ft_strlen(MSH);
	j = (int) ft_strlen(s);
	while (i >= 0 && j >= 0 && MSH[i] == s[j])
	{
		i--;
		j--;
	}
	if (i == -1)
		g_fix_sigquit = 1;
}
