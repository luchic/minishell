#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int	handle_output_redirection(t_command *cmd, const char *path, int append)
{
	int	flags;
	int	fd;

	if (append == 1)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(path, flags, 0644);
	if (fd < 0)
	{
		ft_printf_fd(STDERR, "%s: %s\n", path, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT) == -1)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	ft_log_fd(LOG_INFO, STDERR, "Output file %s opened for writing (append=%d), fd=%d\n", path, append, fd); /// to delete --- IGNORE ---
	close(fd);
	cmd->fd_out = STDOUT;
	return (EXIT_SUCCESS);
}
