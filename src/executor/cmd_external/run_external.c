
#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "ft_common.h"
#include "libft.h"
#include "minishell.h"
#include <sys/stat.h> 


int	run_external_no_fork(t_command *cmd)
{
	char	*path;
	int		is_path_malloced;

	is_path_malloced = 0;
	path = NULL;
	if (ft_strchr((cmd->args)[0], '/'))
	{
		path = (cmd->args)[0];
		if (access(path, F_OK) != 0)
		{
			ft_printf_fd(STDERR, "%s: No such file or directory\n",
				cmd->name);
			ft_log_fd(LOG_ERROR, STDERR, "Exiting with code 127\n"); ///to delete --- IGNORE ---
			free_and_exit(cmd->mnsh, 127);
		}
	}
	else
	{
		path = get_cmd_path(cmd->name, cmd->mnsh->envp);
		if (!path)
		{
			ft_printf_fd(STDERR, "%s: command not found\n",cmd->name);
			ft_log_fd(LOG_ERROR, STDERR, "Exiting with code 127\n"); ///to delete --- IGNORE ---
			free_and_exit(cmd->mnsh, 127);
		}
		is_path_malloced = 1;
	}
	ft_log_fd(LOG_INFO, STDERR, "Resolved command path: %s\n", path); ///to delete --- IGNORE ---

	signal_check();
	
	ft_log_fd(LOG_INFO, STDERR, " cmd->fd_in: %d, cmd->fd_out: %d\n", cmd->fd_in, cmd->fd_out); ///to delete --- IGNORE ---

	execve(path, cmd->args, cmd->mnsh->envp);

	if (is_directory(path))
	{
		ft_printf_fd(STDERR, "%s: Is a directory\n",
			cmd->name);
		ft_log_fd(LOG_ERROR, STDERR, "Exiting with code 126\n"); ///to delete --- IGNORE ---
		free_and_exit(cmd->mnsh, 126);
	}
	if (access(path, X_OK) != 0)
	{
		ft_printf_fd(STDERR, "%s: Permission denied\n",
			cmd->name);
		free(path);
		free_and_exit(cmd->mnsh, 126);
	}

	ft_log_fd(LOG_ERROR, STDERR, "%s: execution failed\n",
		cmd->name);
	if (is_path_malloced && path)
		free(path);
	
	ft_log_fd(LOG_ERROR, STDERR, "Exiting with code cannot execute 126\n"); ///to delete --- IGNORE ---
	free_and_exit(cmd->mnsh, 126);
	return (EXIT_FAILURE); // should never reach here
}


int	run_external(t_command *cmd)
{
	pid_t	pid;
	int		status;
	int		current;

	
	pid = fork();
	if (pid < 0)
		return (ft_log_fd(LOG_ERROR, STDERR, "minishell: fork error\n"), EXIT_FAILURE);
	else if (pid == 0)
	{
		if (handle_redirections(cmd) == EXIT_FAILURE)
		{
			ft_log_fd(LOG_ERROR, STDERR, "Failed to handle redirections for command: %s\n", cmd->name ? cmd->name : "(null)"); ///to delete --- IGNORE ---
			free_and_exit(cmd->mnsh, EXIT_FAILURE);
		}
		if (cmd->name && cmd->args[0][0] == '\0' && cmd->args[1])
		{
			cmd->name = cmd->args[1];
			cmd->args = &cmd->args[1];
		}

		run_external_no_fork(cmd);
		free_and_exit(cmd->mnsh, EXIT_FAILURE);
	}
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
		{
			ft_log_fd(LOG_ERROR, STDERR, "minishell: waitpid failed\n"); ///to delete --- IGNORE ---
			return (EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			ft_log_fd(LOG_INFO, STDERR, "Child exited with status %d\n", WEXITSTATUS(status)); ///to delete --- IGNORE ---
			return (WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			ft_log_fd(LOG_INFO, STDERR, "Child terminated by signal %d\n", WTERMSIG(status)); ///to delete --- IGNORE ---
			return (WTERMSIG(status));
		}
		ft_log_fd(LOG_INFO, STDERR, "child exited abnormally with status %d\n", status); ///to delete --- IGNORE ---
	}
	return (EXIT_FAILURE);
}
