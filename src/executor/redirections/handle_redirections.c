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
	t_redir_type	last_type;

	status = EXIT_SUCCESS;
	current = cmd->redirections;
	while (current)
	{
		redir = (t_redirection *)current->content;
		ft_log_fd(LOG_INFO, STDERR, "Handling redirection: type=%d, value=%s\n", redir->type, redir->value); ///to delete --- IGNORE ---
		
		if (redir->type == last_type)
		{
			ft_log_fd(LOG_INFO, STDERR, "Skipping redundant redirection of type %d\n", redir->type); ///to delete --- IGNORE ---
			current = current->next;
			continue;
		}

		if (redir->type == REDIR_INPUT)
		{
			status = handle_input_redirection(cmd, redir->value);
			last_type = REDIR_INPUT;
		}
		else if (redir->type == REDIR_OUTPUT)
		{
			status = handle_output_redirection(cmd, redir->value, 0);
			last_type = REDIR_OUTPUT;
		}
		else if (redir->type == REDIR_APPEND)
		{
			status = handle_output_redirection(cmd, redir->value, 1);
			last_type = REDIR_APPEND;
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			status = handle_heredoc(redir, cmd);
			last_type = REDIR_HEREDOC;
		}
		if (status == EXIT_FAILURE)
			return (status);


		current = current->next;
	}
	return (status);
}
