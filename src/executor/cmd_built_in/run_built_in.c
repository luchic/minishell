
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
	t_command	tmp_cmd;


	tmp_cmd = *cmd;
	if (tmp_cmd.name && tmp_cmd.args[0][0] == '\0' && tmp_cmd.args[1])
	{
		tmp_cmd.name = cmd->args[1];
		tmp_cmd.args = &cmd->args[1];
	}
	else if (tmp_cmd.name && tmp_cmd.args[0][0] == '\0')
	{
		return (EXIT_SUCCESS);
	}

	orig_fds[0] = dup(STDIN);
	orig_fds[1] = dup(STDOUT);

	if (handle_redirections(cmd) == EXIT_FAILURE)
	{
		dup2(orig_fds[0], STDIN);
		dup2(orig_fds[1], STDOUT);
		close(orig_fds[0]);
		close(orig_fds[1]);
		return (EXIT_FAILURE);
	}

	status = match_built_in(&tmp_cmd);

	if (dup2(orig_fds[0], STDIN) == -1)
		return (ft_log_fd(LOG_ERROR, STDERR, "%s", PREFIX, "dup2 error on fd_in\n"), close(orig_fds[0]), close(orig_fds[1]), EXIT_FAILURE);
	if (dup2(orig_fds[1], STDOUT) == -1)
		return (ft_log_fd(LOG_ERROR, STDERR, "%s", PREFIX, "dup2 error on fd_out\n"), close(orig_fds[0]), close(orig_fds[1]), EXIT_FAILURE);
	close(orig_fds[0]);
	close(orig_fds[1]);
    return (status);
}


