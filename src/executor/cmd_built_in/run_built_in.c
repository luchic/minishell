
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

int	match_built_in(t_command *cmd)
{
	int status;

	status = 0;
	if (ft_strcmp(cmd->name, "echo") == 0)
		status = ft_echo(cmd);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		status = ft_cd(cmd);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		status = ft_pwd(cmd);
	else if (ft_strcmp(cmd->name, "export") == 0)
		status = ft_export(cmd);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		status = ft_unset(cmd);
	else if (ft_strcmp(cmd->name, "env") == 0)
		status = ft_env(cmd);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		status = ft_exit(cmd);

	return (status);
}

int run_builtin(t_command *cmd)
{
	int	orig_fds[2];
	int	status;

	orig_fds[0] = dup(STDIN);
	orig_fds[1] = dup(STDOUT);

	if (handle_redirections(cmd) == EXIT_FAILURE)
		return (ft_log_fd(LOG_ERROR, STDERR, "Failed to handle redirections for command: %s\n", cmd->name ? cmd->name : "(null)"), EXIT_FAILURE);

	//handle_io_redirection(cmd);

	status = match_built_in(cmd);

	if (dup2(orig_fds[0], STDIN) == -1)
		return (ft_log_fd(LOG_ERROR, STDERR, "%s", PREFIX, "dup2 error on fd_in\n"), close(orig_fds[0]), close(orig_fds[1]), EXIT_FAILURE);
	if (dup2(orig_fds[1], STDOUT) == -1)
		return (ft_log_fd(LOG_ERROR, STDERR, "%s", PREFIX, "dup2 error on fd_out\n"), close(orig_fds[0]), close(orig_fds[1]), EXIT_FAILURE);
	close(orig_fds[0]);
	close(orig_fds[1]);
    return (status);
}


