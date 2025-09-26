/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_external.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:44:22 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/26 09:10:07 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <sys/stat.h>

static void	check_return_cmd_path(t_command *cmd, char **path,
		int *is_path_malloced)
{
	*is_path_malloced = 0;
	*path = NULL;
	if (ft_strchr((cmd->args)[0], '/'))
	{
		*path = (cmd->args)[0];
		if (access(*path, F_OK) != 0)
		{
			ft_printf_fd(STDERR, "%s: No such file or directory\n", cmd->name);
			free_and_exit(cmd->mnsh, 127);
		}
	}
	else
	{
		*path = get_cmd_path(cmd->name, cmd->mnsh->envp);
		if (!*path)
		{
			ft_printf_fd(STDERR, "%s: command not found\n", cmd->name);
			free_and_exit(cmd->mnsh, 127);
		}
		*is_path_malloced = 1;
	}
}

int	run_external_no_fork(t_command *cmd)
{
	char	*path;
	int		is_path_malloced;

	check_return_cmd_path(cmd, &path, &is_path_malloced);
	execve(path, cmd->args, cmd->mnsh->envp);
	if (is_directory(path))
	{
		ft_printf_fd(STDERR, "%s: Is a directory\n", cmd->name);
		free_and_exit(cmd->mnsh, 126);
	}
	if (access(path, X_OK) != 0)
	{
		ft_printf_fd(STDERR, "%s: Permission denied\n", cmd->name);
		if (is_path_malloced && path)
			free(path);
		free_and_exit(cmd->mnsh, 126);
	}
	ft_log_fd(LOG_ERROR, STDERR, "%s: execution failed\n", cmd->name);
	if (is_path_malloced && path)
		free(path);
	free_and_exit(cmd->mnsh, 126);
	return (EXIT_FAILURE);
}

static int	parent_process(t_command *cmd, pid_t pid)
{
	int	current;
	int	status;

	if (cmd->mnsh->is_background)
		return (EXIT_SUCCESS);
	if (cmd->fd_in != STDIN)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT)
		close(cmd->fd_out);
	current = waitpid(pid, &status, 0);
	signal(SIGINT, handle_signal_interactive);
	if (current == -1)
		return (EXIT_FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) + 128 == 130)
			ft_printf("\n");
		return (WTERMSIG(status) + 128);
	}
	return (EXIT_FAILURE);
}

int	run_external(t_command *cmd)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (signal(SIGINT, SIG_IGN), ft_log_fd(LOG_ERROR, STDERR,
				"minishell: fork error\n"), EXIT_FAILURE);
	else if (pid == 0)
	{
		reset_signals_to_default();
		setup_io_fds(cmd->fd_in, cmd->fd_out);
		handle_assignments_and_run(cmd->mnsh, cmd, &status,
			run_external_no_fork);
		free_and_exit(cmd->mnsh, status);
	}
	close_previous_fd(cmd->fd_in);
	close_previous_fd(cmd->fd_out);
	return (parent_process(cmd, pid));
}
