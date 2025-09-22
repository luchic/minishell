#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_executor.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


int	handle_redirections(t_command *cmd)
{
    t_redirection *redir;
    int status = EXIT_SUCCESS;

    if (!cmd->redirections)
        return EXIT_SUCCESS;

    redir = (t_redirection *)cmd->redirections->content;
    ft_log_fd(LOG_INFO, STDERR, "Handling redirection: type=%d, value=%s\n", redir->type, redir->value);

    if (redir->type == REDIR_INPUT)
        status = handle_input_redirection(cmd, redir->value);
    else if (redir->type == REDIR_OUTPUT)
        status = handle_output_redirection(cmd, redir->value, 0);
    else if (redir->type == REDIR_APPEND)
        status = handle_output_redirection(cmd, redir->value, 1);
    else if (redir->type == REDIR_HEREDOC)
        status = handle_heredoc(redir, cmd);

    return status;
}

