#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_executor.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>



int handle_output_redirection(t_command *cmd, const char *path, int append/* , t_redir_type *last_type */)
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
        ft_printf_fd(STDERR, "%s: %s\n", path, strerror(errno));
        //ft_printf_fd(STDERR, "%s: No such file or directory\n", path);
        return (EXIT_FAILURE);
    }

    // if (*last_type == REDIR_OUTPUT && append == 0)
    // {
    //     ft_log_fd(LOG_INFO, STDERR, "Skipping redundant redirection of type %d\n", *last_type); ///to delete --- IGNORE ---
    //     close(fd);
    //     return (EXIT_SUCCESS);
    // }

    if (dup2(fd, STDOUT) == -1) 
    {
        close(fd); 
        ft_log_fd(LOG_ERROR, STDERR, "minishell: dup2 failed for output redirection to %s\n", path); ///to delete --- IGNORE ---
        return (EXIT_FAILURE);
    }
    
    ft_log_fd(LOG_INFO, STDERR, "Output file %s opened for writing (append=%d), fd=%d\n", path, append, fd); ///to delete --- IGNORE ---
    close(fd);
    // if (append)
    //     *last_type = REDIR_APPEND;
    // else
    //     *last_type = REDIR_OUTPUT;
    cmd->fd_out = STDOUT; // important
    ft_log_fd(LOG_INFO, STDERR, "Output redirection applied: fd_out=%d\n", cmd->fd_out); ///to delete --- IGNORE ---
    return (EXIT_SUCCESS);
}