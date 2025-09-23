# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"
#include "ft_common.h"


void	close_pipes(int pipe_fds[2])
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

static t_minishell *get_mnsh_from_node(t_ast_node *node)
{
    if (!node) 
		return (NULL);
    if (node->type == COMMAND) 
		return (node->command->mnsh);
    if (node->type == SUBSHELL) 
		return (node->subshell->mnsh);
    return (NULL);
}


pid_t fork_and_exe(t_pipeline *pipeline, int i, int fds[2], int pipe_fds[2])
{
	pid_t pid;
	int status;
	t_ast_node *current_node;
	t_minishell *mnsh;
	
	pid = fork();
	if (pid == -1)
		return (-1);

	if (pid == 0)
	{
		current_node = pipeline->commands[i];
		mnsh = get_mnsh_from_node(current_node);

    	if (dup2(fds[0], STDIN_FILENO) == -1 || dup2(fds[1], STDOUT_FILENO) == -1)
            free_and_exit(mnsh, EXIT_FAILURE);

		if (fds[0] != STDIN)
			close(fds[0]);
		if (fds[1] != STDOUT)
			close(fds[1]);

        if (i < pipeline->count - 1)
            close_pipes(pipe_fds);

		status = EXIT_FAILURE;
		if (current_node->type == COMMAND)
		{
			if (handle_redirections(current_node->command) == EXIT_FAILURE)
				free_and_exit(mnsh, EXIT_FAILURE);
			status = execute_command_pipeline(mnsh, current_node->command);
		}
		else if (current_node->type == SUBSHELL)
		{
			status = execute_subshell(mnsh, current_node->subshell);
		}
		else
		{
			ft_printf_fd(STDERR, "minishell: unknown node type in pipeline\n");
		}
		free_and_exit(mnsh, status);

	}
	else
	{
		if (fds[0] != STDIN)
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
