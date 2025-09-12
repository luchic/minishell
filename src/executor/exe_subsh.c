
// return exit status of the subshell execution
/*
all executions happen in the child process
*/

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	execute_subshell(t_minishell *mnsh, t_subshell *subsh)
{
	pid_t	pid;
	int		status;

	if (!mnsh || !subsh || !subsh->script)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);  // defult action: terminate the process
		signal(SIGQUIT, SIG_DFL); // defult action: core dump
        // TODO: free minishell memory in child process
        //free_stack_minishell(mnsh); // free parent process memory
        //rl_clear_history();
		exit(execute_script(mnsh, subsh->script));
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
}
