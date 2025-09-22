#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_executor.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int	handle_io_redirection(t_command *cmd)
{
	
	if (cmd->fd_in != STDIN)
	{
		if (dup2(cmd->fd_in, STDIN) == -1)
		{
			ft_log_fd(LOG_ERROR, STDERR, "%s",PREFIX, "dup2 error on fd_in\n");
			return (EXIT_FAILURE);
		}
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT)
	{
		if (dup2(cmd->fd_out, STDOUT) == -1)
		{
			ft_log_fd(LOG_ERROR, STDERR, "%s", PREFIX, "dup2 error on fd_out\n");
			return (EXIT_FAILURE);
		}
		close(cmd->fd_out);
	}
	ft_log_fd(LOG_INFO, STDERR, "IO redirection applied: fd_in=%d, fd_out=%d\n", cmd->fd_in, cmd->fd_out); ///to delete --- IGNORE ---
	return (EXIT_SUCCESS);
}



int	handle_redirections(t_command *cmd)
{
	t_list *current;
	t_redirection *redir;
	int		status;

	if (!cmd->redirections)
		return (EXIT_SUCCESS);
	
	if (!cmd->redirections)
		return (EXIT_SUCCESS);
	status = EXIT_SUCCESS;
	current = cmd->redirections;
	while (current)
	{
		redir = (t_redirection *)current->content;
		ft_log_fd(LOG_INFO, STDERR, "Handling redirection: type=%d, value=%s\n", redir->type, redir->value); ///to delete --- IGNORE ---
		if (redir->type == REDIR_INPUT)
		{
			status = handle_input_redirection(cmd, redir->value);
		}
		else if (redir->type == REDIR_OUTPUT)
		{
			status = handle_output_redirection(cmd, redir->value, 0);
		}
		else if (redir->type == REDIR_APPEND)
		{
			status = handle_output_redirection(cmd, redir->value, 1);
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			status = handle_heredoc(redir, cmd);
		}
		if (status == EXIT_FAILURE)
			return (status);


		current = current->next;
	}
	return (status);
}

