/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:39:16 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/24 19:21:11 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_common.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

void	signal_check(void)
{
	signal(SIGINT, SIG_DFL);  // Ctrl+C
	signal(SIGQUIT, SIG_DFL); // core dump
}

void	handle_signal(int signum)
{	
	t_minishell	*mnsh;

	mnsh = *get_mnsh();
	if (!mnsh || (signum == SIGINT && !mnsh->is_running)) //(Ctrl+C)
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
// Handle signals for interactive mode in the main function
//
void	init_signal_handler(void)
{
	signal(SIGINT, handle_signal); // Ctrl+C
	signal(SIGQUIT, SIG_IGN);      // Ctrl+\-> core dump in the child process
}
