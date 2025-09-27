/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:00:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/27 17:05:03 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mnsh;
	int			exit_code;

	(void)argc;
	(void)argv;
	if (init_minishell(&mnsh, envp) == -1)
		return (EXIT_FAILURE);
	init_signal_handler();
	exit_code = run_loop(&mnsh);
	if (mnsh.is_tty_in)
		ft_printf_fd(mnsh.fd, "exit\n");
	if (mnsh.fd != STDOUT)
		close(mnsh.fd);
	return (exit_code);
}
