# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

// infile.txt < ls -l | grep "minishell" | wc -l > outfile.txt


int execute_pipeline(t_minishell *mnsh, t_pipeline *pipeline)
{
	int fds[2];
	int pipe_fds[2];
	pid_t **pids;
	int i;

	pids = malloc(sizeof(pid_t *) * pipeline->count);
	if (!pids)
		return (perror("malloc"), EXIT_FAILURE);

	i = 0;
	fds[0] = pipeline->commands[i]->command->fd_in;
	while (i < pipeline->count)
	{
		if (pipeline->commands[i]->type == SUBSHELL)
			return (free(pids), execute_subshell(mnsh, pipeline->commands[i]->subshell));

		if (i < pipeline->count - 1)
		{
			if (pipe(pipe_fds) == -1)
				return (free(pids), perror("pipe"), EXIT_FAILURE);
			fds[1] = pipe_fds[1];
		}
		else
			fds[1] = pipeline->commands[i]->command->fd_out;

		pids[i] = fork_and_exe(pipeline, i, fds, pipe_fds);
		if (pids[i] == NULL)
			return (free(pids), EXIT_FAILURE);

		i++;
	}
	int result = finish_execution(&pids, pipeline->count);
	free(pids);
	return (result);
}


