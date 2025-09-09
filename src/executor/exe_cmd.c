
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

int execute_command(t_minishell *mnsh, t_command *cmd)
{
    int	orig_fd_in;
	int	orig_fd_out;
	char	**original_env;
	int status;

	//backup original fds
	orig_fd_in = dup(cmd->fd_in);
	orig_fd_out = dup(cmd->fd_out);
	//handle redirections, maybe different in each scenario
	if (cmd->fd_in != STDIN)
	{
		dup2(cmd->fd_in, STDIN);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT)
	{
		dup2(cmd->fd_out, STDOUT);
		close(cmd->fd_out);
	}

	// assignemnts without command
	if (cmd->assignments && !cmd->name)
	{
		handle_assignments(mnsh, cmd->assignments);
		return (0);
	}

	//execute based on command type
	if (cmd->type == CMD_BUILTIN)
    {
        original_env = handle_assignments(mnsh, cmd->assignments);
		status = run_builtin(cmd);
		if (original_env)
		{
			free_array(mnsh->envp);
			mnsh->envp = original_env;
		}
		return (status);
    }
    else if (cmd->type == CMD_EXTERNAL)
    {
		status = run_external(cmd);
		return (status);
    }
    //else if (cmd->type == CMD_HEREDOC)
    //{
        // handle here document
        // e.g., << EOF ... EOF
        // create a temporary file or use a pipe to store the here doc content
        // return 0 for success
    //}
    else
    {
        ft_printf_fd(STDERR, ": command not found: %s\n", cmd->name);
    }

	//restore original fds
	dup2(orig_fd_in, STDIN);
	dup2(orig_fd_out, STDOUT);
	close(orig_fd_in);
	close(orig_fd_out);
    return (0);
}
