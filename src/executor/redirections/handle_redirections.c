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

	if (!cmd->redirections)
		return (1);
	current = cmd->redirections;
	while (current)
	{
		redir = (t_redirection *)current->content;
		if (redir->type == REDIR_INPUT)
		{
			if (!handle_input_redirection(redir, cmd))
				return (0);
		}
		else if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
		{
			if (!handle_output_redirection(redir, cmd))
				return (0);
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			if (!handle_heredoc(redir, cmd))
				return (0);
		}
		current = current->next;
	}
	return (1);
}
