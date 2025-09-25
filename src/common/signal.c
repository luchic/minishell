/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:39:16 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/25 21:08:35 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_common.h"
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
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
	if (mnsh)
		mnsh->last_exit_status = 130;
}

void	init_signal_handler(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void    handle_signal_interactive(int signum)
{
    if (signum == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    init_interactive_signals(void)
{
    signal(SIGINT, handle_signal_interactive);
    signal(SIGQUIT, SIG_IGN); // Ctrl-\: 忽略
}

void	reset_signals_to_default(void)
{
	// 这是一个辅助函数，用于在子进程中恢复默认信号处理
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

