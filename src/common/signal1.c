
#include "ft_common.h"
#include "ft_defines.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

void	signal_check(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_signal(int signum)
{
	t_minishell	*mnsh;

	mnsh = *get_mnsh();
	if (!mnsh || (signum == SIGINT && !mnsh->is_running))
	{
		write(mnsh->fd, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(mnsh->fd, "\n", 1);
	if (mnsh)
		mnsh->last_exit_status = 130;
}

void	init_signal_handler(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
