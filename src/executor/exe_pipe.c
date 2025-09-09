

# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

// infile.txt < ls -l | grep "minishell" | wc -l > outfile.txt


int execute_pipeline(t_minishell *mnsh, t_pipeline *pipeline)
{

	int fds[2];
	// int prev_fd; // fds[0] of previous_fd
	// int current_fdout; // fds[1] of current_fd_write_end
    int pipe_fds[2];
    pid_t *pids;
	int i;

	i = 0;
	fds[0] = pipeline->commands[i]->command->fd_in;
	while (i < pipeline->count)
	{
		if (pipeline->commands[i]->type == SUBSHELL)
			return (execute_subshell(mnsh, &(pipeline->commands[0]->subshell)));
        if (pipeline->commands[i]->type != COMMAND) // to be deleted
            return (perror("wrong parsing. check again!"), EXIT_FAILURE); // should not happen, to delete

        if (i < pipeline->count - 1)
        {
            if (pipe(pipe_fds) == -1)
				return (perror("pipe"), EXIT_FAILURE);
			fds[1] = pipe_fds[1];
		}
		else
			fds[1] = pipeline->commands[i]->command->fd_out;

		pids = malloc(sizeof(pid_t) * pipeline->count);
		if (!pids)
			return (perror("malloc"), EXIT_FAILURE);
		pids[i] = fork_and_exe(pipeline, i, fds, pipe_fds);
		if (pids[i] == NULL)
			return (EXIT_FAILURE);
		i++;
	}
    return (finish_execution(&pids, pipeline->count));
}


