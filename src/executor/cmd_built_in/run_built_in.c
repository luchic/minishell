
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

int run_builtin(t_command *cmd)
{
	int	orig_fds[2];
	int	status;

	orig_fds[0] = dup(STDIN);
	orig_fds[1] = dup(STDOUT);

	if (cmd->fd_in != STDIN)
	{
		if (dup2(cmd->fd_in, STDIN) == -1)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT)
	{
		if (dup2(cmd->fd_out, STDOUT) == -1)
			return (perror("dup2"), dup2(orig_fds[0], STDIN), close_pipes(orig_fds), EXIT_FAILURE);
		close(cmd->fd_out);
	}
	//execute built-in
	status = match_built_in(cmd->name);

	if (dup2(orig_fds[0], STDIN) == -1)
		return (perror("dup2"), close(orig_fds[0]), close(orig_fds[1]), EXIT_FAILURE);
	if (dup2(orig_fds[1], STDOUT) == -1)
		return (perror("dup2"), close(orig_fds[0]), close(orig_fds[1]), EXIT_FAILURE);
	close(orig_fds[0]);
	close(orig_fds[1]);
    return (status);
}

int	match_built_in(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}
