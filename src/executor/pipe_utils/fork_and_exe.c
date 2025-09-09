
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

void	close_pipes(int pipe_fds[2])
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}


pid_t fork_and_exe(t_pipeline *pipeline, int i, int fds[2], int pipe_fds[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		if (fds[0] != STDIN)
		{
			dup2(fds[0], STDIN);
			close(fds[0]);
		}
		if (fds[1] != STDOUT)
		{
			dup2(fds[1], STDOUT);
			if (i < pipeline->count - 1)
				close_pipes(pipe_fds);
		}
		execute_command(pipeline->commands[i]->command->mnsh, pipeline->commands[i]->command);
	}
	else
	{
		if (fds[0] != STDIN)
			close(fds[0]);
		if (i < pipeline->count - 1)
			close(pipe_fds[1]);
		fds[0] = pipe_fds[0];
	}
	return (pid);
}

int	finish_execution(pid_t **pids, int count)
{
	int	status;
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (i < count)
	{
		if (waitpid((*pids)[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit_status = EXIT_FAILURE;
		}
		else if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = 128 + WTERMSIG(status); // 128 is a conventino in bash
		i++;
	}
	free(*pids);
	return (exit_status);
}
