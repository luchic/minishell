/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:31:11 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 17:12:32 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

void	handle_signal_heredoc(int signum)
{
	t_minishell	*mnsh;

	mnsh = *get_mnsh();
	if (signum == SIGINT)
	{
		mnsh->last_exit_status = 2;
		write(mnsh->fd, "> ^C\n", 5);
		close(STDIN);
	}
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal_heredoc(void)
{
	signal(SIGINT, handle_signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals_to_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
