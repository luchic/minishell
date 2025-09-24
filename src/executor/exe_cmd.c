
#include "expander.h"
#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"


int	execute_command(t_minishell *mnsh, t_command *cmd)
{
	char	**original_env;
	int		status;
	int		should_restore_env;
	int		orig_fds[2];
	int		is_builtin_with_redir;

	status = 0;
	orig_fds[0] = -1;
	orig_fds[1] = -1;
	is_builtin_with_redir = 0;
	original_env = NULL;
	should_restore_env = 0;
	if (!cmd->name && !cmd->assignments)
		return (EXIT_SUCCESS);
	if (preprocess_cmd(cmd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (handle_redirections(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!cmd->name)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (cmd->assignments)
		{
			original_env = handle_assignments(mnsh, cmd->assignments);
			free_str_array(original_env);
		}
		return (EXIT_SUCCESS);
	}
	if (cmd->type == CMD_BUILTIN)
	{
		orig_fds[0] = dup(STDIN_FILENO);
		orig_fds[1] = dup(STDOUT_FILENO);
		if (cmd->fd_in != STDIN_FILENO)
			dup2(cmd->fd_in, STDIN_FILENO);
		if (cmd->fd_out != STDOUT_FILENO)
			dup2(cmd->fd_out, STDOUT_FILENO);
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		handle_assignments_and_run(mnsh, cmd, &status, run_builtin);
		dup2(orig_fds[0], STDIN_FILENO);
		dup2(orig_fds[1], STDOUT_FILENO);
		close(orig_fds[0]);
		close(orig_fds[1]);
	}
	else if (cmd->type == CMD_EXTERNAL)
	{
		status = run_external(cmd);
	}
	return (status);
}
