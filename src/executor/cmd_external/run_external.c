
#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"

void	cmd_false_exit(t_minishell *mnsh)
{
	free_stack_minishell(mnsh);
	if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}

int	run_external_no_fork(t_command *cmd)
{
	char	*path;
	int		is_path_malloced;

	is_path_malloced = 0;
	if (ft_strchr((cmd->args)[0], '/'))
		path = (cmd->args)[0];
	else
	{
		get_cmd_path(cmd->name, cmd->mnsh->envp, &path);
		if (!path)
		{
			ft_log_fd(LOG_ERROR, STDERR, "%s: command not found\n",
				cmd->name);
			return (127);
		}
		is_path_malloced = 1;
	}
	if (access(path, X_OK) != 0)
	{
		ft_log_fd(LOG_ERROR, STDERR, "%s: Permission denied\n",
			path);
		return (127);
	}
	signal_check();
	handle_assignments(cmd->mnsh, cmd->assignments);
	execve(path, cmd->args, cmd->mnsh->envp);
	ft_log_fd(LOG_ERROR, STDERR, "minishell: %s: %s\n",
		path, strerror(errno));
	if (is_path_malloced && path)
		free(path);
	return (cmd_false_exit(cmd->mnsh), EXIT_FAILURE);
}


int	run_external(t_command *cmd)
{
	pid_t	pid;
	int		status;
	int		current;
	int		exit_code;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), EXIT_FAILURE);
	else if (pid == 0)
		return (run_external_no_fork(cmd));
	else
	{
		if (cmd->mnsh->is_background)
			return (EXIT_SUCCESS);
		if (cmd->fd_in != STDIN)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT)
			close(cmd->fd_out);
		current = waitpid(pid, &status, 0);
		if (current == -1)
			return (perror("waitpid"), EXIT_FAILURE);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			exit_code = WTERMSIG(status);
		else
			exit_code = 1;
	}
	return (exit_code);
}
