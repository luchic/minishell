
#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_executor.h"

void	cmd_false_exit(void)
{
	if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}

int	run_external(t_command *cmd)
{
	pid_t	pid;
	int		status;
	char	*path;
	int		is_path_malloced;
	int		current;
	int		exit_code = 0;

	pid = fork();
	if (pid < 0)
		return (perror("fork"),EXIT_FAILURE);
	else if (pid == 0)
	{
		// Child process
		signal(SIGINT, SIG_DFL); // Ctrl+C
		signal(SIGQUIT, SIG_DFL); // core dump
		handle_assignments(cmd->mnsh, cmd->assignments);
		if (cmd->fd_in != STDIN)
		{
			if (dup2(cmd->fd_in, STDIN) == -1)
			{
				perror("dup2");
				cmd_false_exit();
			}
			close(cmd->fd_in);
		}
		if (cmd->fd_out != STDOUT)
		{
			if (dup2(cmd->fd_out, STDOUT) == -1)
			{
				perror("dup2");
				cmd_false_exit();
			}
			close(cmd->fd_out);
		}
		is_path_malloced = 0;
		if (ft_strchr((cmd->args)[0], '/'))
			path = (cmd->args)[0];
		else
		{
			get_cmd_path(cmd->name, cmd->mnsh->envp, &path);
			is_path_malloced = 1;
		}
		execve(path, cmd->args, cmd->mnsh->envp);
		perror("execve");
		if (is_path_malloced)
			free(path);
		cmd_false_exit();
	}
	else
	{
		// Parent process
		if (cmd->mnsh->is_background) // background process
			return (EXIT_SUCCESS);
		if (cmd->fd_in != STDIN) //should put: && cmd->fd_in != -1?
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT)
			close(cmd->fd_out);
		current = waitpid(pid, &status, 0);
		if (current == -1)
		{
			perror("waitpid");
			return (EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = WTERMSIG(status);
		else
			exit_code = 1;
	}
	return (exit_code);
}
