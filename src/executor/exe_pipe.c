# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

// infile.txt < ls -l | grep "minishell" | wc -l > outfile.txt


int execute_pipeline(t_minishell *mnsh, t_pipeline *pipeline)
{
	int fds[2];
	int pipe_fds[2];
	pid_t *pids;
	int i;
	int result;

	(void)mnsh;
	pids = malloc(sizeof(pid_t) * pipeline->count);
	if (!pids)
		return (perror("malloc"), EXIT_FAILURE);

	fds[0] = STDIN; // pipeline->commands[0]->command->fd_in;
	
	i = 0;
	while (i < pipeline->count)
	{

		if (i < pipeline->count - 1)
		{
			if (pipe(pipe_fds) == -1)
				return (free(pids), perror("pipe"), EXIT_FAILURE);
			fds[1] = pipe_fds[1];
		}
		else
		{
			fds[1] = STDOUT; //pipeline->commands[i]->command->fd_out;
		}

		pids[i] = fork_and_exe(pipeline, i, fds, pipe_fds);
		if (pids[i] == -1)
			return (free(pids), EXIT_FAILURE);

		if (fds[0] != STDIN)
			close(fds[0]);
		if (fds[1] != STDOUT)
			close(pipe_fds[1]);

		if (i < pipeline->count - 1)
		{
			fds[0] = pipe_fds[0];
		}
		i++;
	}
	if (fds[0] != STDIN)
		close(fds[0]);
	result = finish_execution(pids, pipeline->count);
	free(pids);
	return (result);
}

