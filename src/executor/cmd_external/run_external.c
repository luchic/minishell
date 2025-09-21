
#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <sys/stat.h> 

void	cmd_false_exit(t_minishell *mnsh)
{
	if (mnsh)
		free_stack_minishell(mnsh);
	if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}

static int	is_directory(const char *path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode)); // is it forbidden to access a directory?
}

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
			exit (127);
		}
	}
	else
	{
		path = get_cmd_path(cmd->name, cmd->mnsh->envp);
		if (!path)
		{
			ft_printf_fd(STDERR, "%s: command not found\n",cmd->name);
			ft_log_fd(LOG_ERROR, STDERR, "Exiting with code 127\n"); ///to delete --- IGNORE ---
			exit (127);
		}
		is_path_malloced = 1;
	}
	ft_log_fd(LOG_INFO, STDOUT, "Resolved command path: %s\n", path); ///to delete --- IGNORE ---

	signal_check();
	
	handle_io_redirection(cmd);
	ft_log_fd(LOG_INFO, STDERR, " cmd->fd_in: %d, cmd->fd_out: %d\n", cmd->fd_in, cmd->fd_out); ///to delete --- IGNORE ---

	execve(path, cmd->args, cmd->mnsh->envp);

	if (is_directory(path))
	{
		ft_printf_fd(STDERR, "%s: Is a directory\n",
			cmd->name);
		ft_log_fd(LOG_ERROR, STDERR, "Exiting with code 126\n"); ///to delete --- IGNORE ---
		exit (126);
	}
	if (access(path, X_OK) != 0)
	{
		ft_printf_fd(STDERR, "%s: Permission denied\n",
			cmd->name);
		free(path);
		exit (126);
	}

	ft_log_fd(LOG_ERROR, STDERR, "%s: execution failed\n",
		cmd->name);
	if (is_path_malloced && path)
		free(path);
	
	ft_log_fd(LOG_ERROR, STDERR, "Exiting with code cannot execute 126\n"); ///to delete --- IGNORE ---
	exit (126);
}


int	run_external(t_command *cmd)
{
	pid_t	pid;
	int		status;
	int		current;
	// int		exit_code;

	
	pid = fork();
	if (pid < 0)
		return (ft_log_fd(LOG_ERROR, STDERR, "minishell: fork error\n"), EXIT_FAILURE);
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
		{
			ft_log_fd(LOG_DEBUG, STDOUT, "Child exited with status %d\n", WEXITSTATUS(status)); ///to delete --- IGNORE ---
			return (WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			ft_log_fd(LOG_DEBUG, STDOUT, "Child terminated by signal %d\n", WTERMSIG(status)); ///to delete --- IGNORE ---
			return (WTERMSIG(status));
		}
		else
		{
			ft_log_fd(LOG_ERROR, STDERR, "child exited abnormally with status %d\n", status); ///to delete --- IGNORE ---
			return (1);
		}
	}
}
