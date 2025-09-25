#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

static t_minishell	*get_mnsh_from_node(t_ast_node *node)
{
	if (!node)
		return (NULL);
	if (node->type == COMMAND)
		return (node->command->mnsh);
	if (node->type == SUBSHELL)
		return (node->subshell->mnsh);
	return (NULL);
}

static void	child_process(t_pipeline *pipeline, int i, int fds[2],
		int pipe_fds[2])
{
	t_ast_node	*cur_node;
	t_minishell	*mnsh;
	t_command	*cmd;

	cur_node = pipeline->commands[i];
	mnsh = get_mnsh_from_node(cur_node);
	setup_io_fds(fds[0], fds[1]);
	if (i < pipeline->count - 1)
		close(pipe_fds[0]);
	if (cur_node->type == COMMAND)
	{
		cmd = cur_node->command;
		if (handle_redirections(cmd) == EXIT_FAILURE)
			free_and_exit(mnsh, EXIT_FAILURE);
		setup_io_fds(cmd->fd_in, cmd->fd_out);
	}
	if (cur_node->type == COMMAND)
		free_and_exit(mnsh, execute_command_pipeline(mnsh, cur_node->command));
	else if (cur_node->type == SUBSHELL)
		free_and_exit(mnsh, execute_subshell(mnsh, cur_node->subshell));
	else
		free_and_exit(mnsh, EXIT_FAILURE);
}


pid_t	fork_and_exe(t_pipeline *pipeline, int i, int fds[2], int pipe_fds[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		child_process(pipeline, i, fds, pipe_fds);
	}
	else
	{
		if (fds[0] != STDIN_FILENO)
			close(fds[0]);
		if (i < pipeline->count - 1)
			close(pipe_fds[1]);
	}
	return (pid);
}

int	finish_execution(pid_t *pids, int count)
{
	int	status;
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			ft_log_fd(LOG_ERROR, STDERR, "minishell: waitpid failed\n");
			exit_status = EXIT_FAILURE;
		}
		else if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = 128 + WTERMSIG(status);
		i++;
	}
	return (exit_status);
}
