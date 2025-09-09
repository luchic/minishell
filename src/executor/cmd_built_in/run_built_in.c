
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

int run_builtin(t_command *cmd)
{
	int	orig_fd_in;
	int	orig_fd_out;
	int	status;

	orig_fd_in = dup(STDIN);
	orig_fd_out = dup(STDOUT);

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
	//execute built-in
	status = match_built_in(cmd->name);

	dup2(orig_fd_in, STDIN);
	dup2(orig_fd_out, STDOUT);
	close(orig_fd_in);
	close(orig_fd_out);
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
