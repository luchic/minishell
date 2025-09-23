#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_executor.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


int	handle_redirections(t_command *cmd)
{
	t_list *current;
	t_redirection *redir;
	int		status;

	status = EXIT_SUCCESS;
	if (!cmd || !cmd->redirections)
		return (EXIT_SUCCESS);
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
		{
			ft_log_fd(LOG_ERROR, STDERR, "Failed to handle redirection: type=%d, value=%s\n", redir->type, redir->value); ///to delete --- IGNORE ---
			return (EXIT_FAILURE);
		}

		current = current->next;
	}
	return (EXIT_SUCCESS);
}
