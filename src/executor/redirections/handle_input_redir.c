
#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int	open_input_file(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(STDERR, "%s: %s\n", path, strerror(errno));
	}
	return (fd);
}
