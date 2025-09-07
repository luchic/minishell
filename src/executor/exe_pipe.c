/*
for every command, use command
mainly about pipes can directly call execute_command
need to consider heredoc

*/

# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

//ls -l | grep "minishell" | wc -l

int execute_pipeline(t_minishell *mnsh, t_pipeline *pipeline)
{
    int	prev_fd;
	int pipe_fd[2];
	t_command *cmd;
	pid_t *pids;
	int i;

	if (pipeline->commands[0]->type == NODE_SUBSHELL)
		return (execute_subshell(mnsh, &(pipeline->commands[0]->subshell)));
	if (pipeline->commands[0]->type != NODE_COMMAND)
		return (perror("wrong parsing. check again!"), EXIT_FAILURE); // should not happen

	cmd = pipeline->commands[0];
	prev_fd = cmd->fd_in; // could be STDIN
	
    return 0;
}
