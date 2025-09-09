

# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

// infile.txt < ls -l | grep "minishell" | wc -l > outfile.txt

int execute_pipeline(t_minishell *mnsh, t_pipeline *pipeline)
{
    int prev_fd;
    int pipe_fds[2];
    pid_t *pids;
	int i;
    int exit_code;

	i = 0;
	prev_fd = pipeline->commands[i]->command->fd_in; // could be STDIN
	while (i < pipeline->count)
	{
		if (pipeline->commands[i]->type == SUBSHELL)
			return (execute_subshell(mnsh, &(pipeline->commands[0]->subshell)));
        if (pipeline->commands[i]->type != COMMAND)
            return (perror("wrong parsing. check again!"), EXIT_FAILURE); // should not happen

        if (i < pipeline->count - 1)
        {
            pipe(pipe_fds);
        }
        pids[i] = fork();
        if (pids[i] == 0)
        {
            execute_command(mnsh, pipeline->commands[i]);
        }
        else
	}


    return 0;
}
