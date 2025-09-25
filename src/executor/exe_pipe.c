/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:42:52 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/25 17:00:35 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

static int	get_fds_write(t_pipeline *pl, int i, int fds[2], int pipe_fds[2])
{
	if (i < pl->count - 1)
	{
		if (pipe(pipe_fds) == -1)
			return (EXIT_FAILURE);
		fds[1] = pipe_fds[1];
	}
	else
		fds[1] = STDOUT_FILENO;
	return (EXIT_SUCCESS);
}

static int	run_pl_process(t_pipeline *pl, pid_t *pids)
{
	int	fds[2];
	int	pipe_fds[2];
	int	i;

	fds[0] = STDIN_FILENO;
	i = -1;
	while (++i < pl->count)
	{
		if (get_fds_write(pl, i, fds, pipe_fds) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		pids[i] = fork_and_exe(pl, i, fds, pipe_fds);
		if (pids[i] == -1)
			return (EXIT_FAILURE);
		close_previous_fd(fds[1]);
		close_previous_fd(pipe_fds[1]);
		if (i < pl->count - 1)
			fds[0] = pipe_fds[0];
	}
	if (fds[0] != STDIN_FILENO)
		close(fds[0]);
	return (EXIT_SUCCESS);
}

int	execute_pipeline(t_minishell *mnsh, t_pipeline *pipeline)
{
	pid_t		*pids;
	int			status;
	t_ast_node	tmp_node;

	(void)mnsh;
	tmp_node.type = PIPELINE;
	tmp_node.pipeline = pipeline;
	if (preprocess_heredoc_node(&tmp_node) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	pids = malloc(sizeof(pid_t) * pipeline->count);
	if (!pids)
		return (EXIT_FAILURE);
	if (run_pl_process(pipeline, pids) == EXIT_FAILURE)
		return (free(pids), EXIT_FAILURE);
	status = finish_execution(pids, pipeline->count);
	free(pids);
	return (status);
}
