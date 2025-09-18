#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_executor.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


int	handle_output_redirection(t_redirection *redir, t_command *cmd)
{
	int	fd;
	int	flags;

	if (redir->type == REDIR_OUTPUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else 
		flags = O_WRONLY | O_CREAT | O_APPEND;

	fd = open(redir->value, flags, 0644);
	ft_printf_fd(STDOUT, "Opened file %s with fd %d for output redirection\n", redir->value, fd); ///to delete --- IGNORE ---
	if (fd == -1)
	{
		ft_printf_fd(STDERR, "minishell: %s: No such file or directory\n", redir->value);
		return (EXIT_FAILURE);
	}
	if (cmd->fd_out != STDOUT && cmd->fd_out != -1)
		close(cmd->fd_out);
	cmd->fd_out = fd;
	return (EXIT_SUCCESS);
}
