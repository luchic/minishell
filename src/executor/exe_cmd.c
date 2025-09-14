
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

int	execute_command_pipeline(t_minishell *mnsh, t_command *cmd)
{
	char	**original_env;
	int		status;

	// assignemnts without command
	if (cmd->assignments && !cmd->name)
		return (handle_assignments(mnsh, cmd->assignments), 0);

	// Handle redirections
	if (!handle_redirections(cmd))
		return (EXIT_FAILURE);
	
	//handle fd_in and fd_out for pipeline
	if (cmd->fd_in != STDIN && cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN) == -1)
		{
			return (ft_log_fd(LOG_ERROR, STDERR, "minishell: dup2 error on fd_in\n"), EXIT_FAILURE);
		}
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT && cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, STDOUT) == -1)
		{
			return (ft_log_fd(LOG_ERROR, STDERR, "minishell: dup2 error on fd_out\n"), EXIT_FAILURE);
		}
		close(cmd->fd_out);
	}

	if (cmd->type == CMD_BUILTIN)
    {
        original_env = handle_assignments(mnsh, cmd->assignments);
		status = run_builtin(cmd);
		if (original_env)
		{
			free_str_array(mnsh->envp);
			mnsh->envp = original_env;
		}
		return (status);
    }
    else if (cmd->type == CMD_EXTERNAL)
		return (run_external_no_fork(cmd));
    else
        ft_printf_fd(STDERR, ": command not found: %s\n", cmd->name);
    return (0);
}

int execute_command(t_minishell *mnsh, t_command *cmd)
{
	char	**original_env;
	int		status;

	// assignemnts without command
	if (cmd->assignments && !cmd->name)
		return (handle_assignments(mnsh, cmd->assignments), 0);

	// Handle redirections
	if (!handle_redirections(cmd))
		return (EXIT_FAILURE);
	
	//handle fd_in and fd_out for pipeline
	if (cmd->fd_in != STDIN && cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN) == -1)
		{
			return (ft_log_fd(LOG_ERROR, STDERR, "minishell: dup2 error on fd_in\n"), EXIT_FAILURE);
		}
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT && cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, STDOUT) == -1)
		{
			return (ft_log_fd(LOG_ERROR, STDERR, "minishell: dup2 error on fd_out\n"), EXIT_FAILURE);
		}
		close(cmd->fd_out);
	}


	//execute based on command type
	if (cmd->type == CMD_BUILTIN)
    {
        original_env = handle_assignments(mnsh, cmd->assignments);
		status = run_builtin(cmd);
		if (original_env)
		{
			free_str_array(mnsh->envp);
			mnsh->envp = original_env;
		}
		return (status);
    }
    else if (cmd->type == CMD_EXTERNAL)
		return (run_external(cmd));
    else
        ft_printf_fd(STDERR, ": command not found: %s\n", cmd->name);
    return (0);
}
