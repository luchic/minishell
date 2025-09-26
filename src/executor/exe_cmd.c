/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:42:00 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/25 16:42:03 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

static void	init_params(int orig_fds[2], char ***original_env, int *status)
{
	orig_fds[0] = -1;
	orig_fds[1] = -1;
	*original_env = NULL;
	*status = 0;
}

static void	io_and_run_builtin(t_command *cmd, int orig_fds[2], int *status,
		t_minishell *mnsh)
{
	orig_fds[0] = dup(STDIN_FILENO);
	orig_fds[1] = dup(STDOUT_FILENO);
	setup_io_fds(cmd->fd_in, cmd->fd_out);
	handle_assignments_and_run(mnsh, cmd, status, run_builtin);
	dup2(orig_fds[0], STDIN_FILENO);
	dup2(orig_fds[1], STDOUT_FILENO);
	close(orig_fds[0]);
	close(orig_fds[1]);
}

int	execute_command(t_minishell *mnsh, t_command *cmd)
{
	char	**original_env;
	int		status;
	int		orig_fds[2];

	init_params(orig_fds, &original_env, &status);
	if (preprocess_heredoc_cmd(cmd) != EXIT_SUCCESS)
		return (mnsh->last_exit_status = 1, EXIT_FAILURE);
	if (!cmd->name && !cmd->assignments)
		return (EXIT_SUCCESS);
	if (preprocess_cmd(cmd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (!cmd->name)
	{
		close_previous_fd(cmd->fd_in);
		close_previous_fd(cmd->fd_out);
		if (cmd->assignments)
			free_str_array(handle_assignments(mnsh, cmd->assignments));
		return (EXIT_SUCCESS);
	}
	if (cmd->type == CMD_BUILTIN)
		io_and_run_builtin(cmd, orig_fds, &status, mnsh);
	else if (cmd->type == CMD_EXTERNAL)
		status = run_external(cmd);
	return (status);
}
