#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int	open_output_file(const char *path, int append, t_command *cmd)
{
	int	flags;
	int	fd;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;

	close_previous_fd(cmd->fd_out);
	fd = open(path, flags, 0644);
	if (fd < 0)
	{
		ft_printf_fd(STDERR, "%s: %s\n", path, strerror(errno));
		return (EXIT_FAILURE);
	}
	cmd->fd_out = fd;
	return (EXIT_SUCCESS);
}
