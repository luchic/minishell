/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:06:57 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/27 19:33:14 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	ft_write_data_in_child(const char *del, int fd, int is_quoted)
{
	char		*line;
	char		*expanded;

	expanded = NULL;
	while (1)
	{
		line = get_next_line_not_in_tty();
		if (ft_is_limiter(line, del))
		{
			if (line)
				free(line);
			break ;
		}
		if (!line)
			break ;
		if (!is_quoted)
			expanded = expand_heredoc_line(line);
		if (!expanded || is_quoted)
			ft_printf_fd(fd, "%s\n", line);
		else
			ft_printf_fd(fd, "%s\n", expanded);
		if (expanded)
			free(expanded);
		free(line);
	}
}

static void	run_process_heredoc(const char *del, int fd, int is_quoted)
{
	t_minishell	*mnsh;

	init_signal_heredoc();
	ft_write_data_in_child(del, fd, is_quoted);
	close(fd);
	rl_clear_history();
	mnsh = *get_mnsh();
	if (mnsh)
		free_stack_minishell(mnsh);
	if (mnsh && mnsh->last_exit_status)
		exit(mnsh->last_exit_status);
	exit(EXIT_SUCCESS);
}

int	save_data_heredoc(const char *del, int fd, char *filename, int is_quoted)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (ft_log_fd(LOG_ERROR, STDERR, "heredoc: fork failed\n"),
			EXIT_FAILURE);
	if (pid == 0)
	{
		(free(filename), run_process_heredoc(del, fd, is_quoted));
	}
	else
	{
		ignore_signals();
		if (waitpid(pid, &status, 0) == -1)
		{
			ft_log_fd(LOG_ERROR, STDERR, "minishell: heredoc waitpid failed\n");
			init_signal_handler();
			return (EXIT_FAILURE);
		}
		init_signal_handler();
		if (WEXITSTATUS(status) + 128 == 130)
			return (WEXITSTATUS(status) + 128);
	}
	return (0);
}
