#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_executor.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>



int handle_output_redirection(t_command *cmd, const char *path, int append)
{
    int flags;
    int fd;

    if (append == 1)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else
        flags = O_WRONLY | O_CREAT | O_TRUNC;

    fd = open(path, flags, 0644);

    if (fd < 0)
    {
        ft_log_fd(LOG_ERROR, STDERR, "minishell: %s: No such file or directory\n", path); ///to delete --- IGNORE ---
        return (EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT) == -1) 
    {
        close(fd); 
        ft_log_fd(LOG_ERROR, STDERR, "minishell: dup2 failed for output redirection to %s\n", path); ///to delete --- IGNORE ---
        return (EXIT_FAILURE);
    }
    
    ft_log_fd(LOG_INFO, STDERR, "Output file %s opened for writing (append=%d), fd=%d\n", path, append, fd); ///to delete --- IGNORE ---
    close(fd);
    cmd->fd_out = STDOUT; // important
    ft_log_fd(LOG_INFO, STDERR, "Output redirection applied: fd_out=%d\n", cmd->fd_out); ///to delete --- IGNORE ---
    return (EXIT_SUCCESS);
}