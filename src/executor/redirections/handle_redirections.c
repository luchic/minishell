#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int	handle_redirections(t_command *cmd)
{
	t_list			*current;
	t_redirection	*redir;
	int				temp_fd;

	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	if (!cmd || !cmd->redirections)
		return (EXIT_SUCCESS);
	current = cmd->redirections;
	while (current)
	{
		redir = (t_redirection *)current->content;
		temp_fd = -1;
		if (redir->type == REDIR_INPUT)
		{
			close_previous_fd(cmd->fd_in);
			temp_fd = open_input_file(redir->value);
			if (temp_fd == -1)
				return (EXIT_FAILURE);
			cmd->fd_in = temp_fd;
		}
		else if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
		{
			close_previous_fd(cmd->fd_out);
			temp_fd = open_output_file(redir->value,
					(redir->type == REDIR_APPEND));
			if (temp_fd == -1)
				return (EXIT_FAILURE);
			cmd->fd_out = temp_fd;
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			close_previous_fd(cmd->fd_in);
			if (handle_heredoc(redir, cmd) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
