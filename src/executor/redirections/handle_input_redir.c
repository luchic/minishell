
#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_executor.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int	handle_input_redirection(t_redirection *redir, t_command *cmd)
{
	int	fd;

	fd = open(redir->value, O_RDONLY);
	ft_log_fd(LOG_DEBUG, STDOUT, "handle_input_redirection: Opening file %s for input redirection\n", redir->value);
	if (fd == -1)
	{
		ft_printf_fd(STDERR, "minishell: %s: No such file or directory\n", redir->value);
		return (EXIT_FAILURE);
	}

	ft_log_fd(LOG_DEBUG, STDOUT, "Input redirection: setting cmd->fd_in from %d to %d\n", cmd->fd_in, fd);
	if (cmd->fd_in != STDIN && cmd->fd_in != -1)
		close(cmd->fd_in);

	ft_log_fd(LOG_DEBUG, STDOUT, "Input redirection: cmd->fd_in set to %d\n", fd);
	cmd->fd_in = fd;
	return (EXIT_SUCCESS);
}
