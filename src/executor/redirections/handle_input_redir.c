
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
	if (fd == -1)
	{
		ft_printf_fd(STDERR, "minishell: %s: No such file or directory\n", redir->value);
		return (0);
	}
	if (cmd->fd_in != STDIN && cmd->fd_in != -1)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	return (1);
}
