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
	int				temp_res;
	int				status;

	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	if (!cmd || !cmd->redirections)
		return (EXIT_SUCCESS);
	current = cmd->redirections;
	status = EXIT_SUCCESS;
	while (current)
	{
		redir = (t_redirection *)current->content;
		temp_res = -1;
		if (redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC)
			status = open_input_file(redir->value, cmd);
		else if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
			status = open_output_file(redir->value, redir->type == REDIR_APPEND,
					cmd);
		current = current->next;
	}
	return (status);
}
