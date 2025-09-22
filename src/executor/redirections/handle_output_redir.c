#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_executor.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


// int	handle_output_redirection(t_redirection *redir, t_command *cmd)
// {
// 	int	fd;
// 	int	flags;

// 	if (redir->type == REDIR_OUTPUT)
// 		flags = O_WRONLY | O_CREAT | O_TRUNC;
// 	else 
// 		flags = O_WRONLY | O_CREAT | O_APPEND;

// 	fd = open(redir->value, flags, 0644);

// 	ft_log_fd(LOG_DEBUG, STDERR, "handle_output_redirection: Opening file %s for output redirection with flags %d\n", redir->value, flags); ///to delete --- IGNORE ---
// 	if (fd == -1)
// 	{
// 		ft_log_fd(LOG_ERROR, STDERR, "minishell: %s: No such file or directory\n", redir->value);
// 		return (EXIT_FAILURE);
// 	}
// 	if (cmd->fd_out != STDOUT && cmd->fd_out != -1)
// 		close(cmd->fd_out);
// 	cmd->fd_out = fd;
// 	ft_log_fd(LOG_INFO, STDERR, "Output redirection set: fd_out=%d\n", cmd->fd_out); ///to delete --- IGNORE ---
// 	return (EXIT_SUCCESS);
// }

int handle_output_redirection(t_command *cmd, const char *path, int append)
{
    int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
    int fd = open(path, flags, 0644);
    if (fd < 0)
        return (perror(path), EXIT_FAILURE);
    if (dup2(fd, STDOUT) == -1) 
    {
        int e = errno; close(fd); errno = e;
        return (perror("dup2"), EXIT_FAILURE);
    }
    ft_log_fd(LOG_INFO, STDERR, "Output file %s opened for writing (append=%d), fd=%d\n", path, append, fd); ///to delete --- IGNORE ---
    close(fd);
    cmd->fd_out = STDOUT; // important
    ft_log_fd(LOG_INFO, STDERR, "Output redirection applied: fd_out=%d\n", cmd->fd_out); ///to delete --- IGNORE ---
    return (EXIT_SUCCESS);
}