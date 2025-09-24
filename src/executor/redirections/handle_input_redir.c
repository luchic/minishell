
#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int	handle_input_redirection(t_command *cmd, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	ft_log_fd(LOG_INFO, STDERR, "Opening input file %s for reading, fd=%d\n",
		path, fd); /// to delete --- IGNORE ---
	if (fd < 0)
	{
		ft_printf_fd(STDERR, "%s: %s\n", path, strerror(errno));
		// ft_printf_fd(STDERR, " No such file or directory\n");
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN) == -1)
	{
		close(fd);
		ft_log_fd(LOG_ERROR, STDERR,
			"minishell: dup2 failed for input redirection from %s\n", path);
			/// to delete --- IGNORE ---
		return (EXIT_FAILURE);
	}
	close(fd);
	ft_log_fd(LOG_INFO, STDERR, "Input file %s opened for reading, fd=%d\n",
		path, fd); /// to delete --- IGNORE ---
	cmd->fd_in = STDIN;
	return (EXIT_SUCCESS);
}
