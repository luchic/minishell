/*
check which command type
external: use fork + execve
built-in: call the function directly
assignment: update the variable in mnsh->variables
special: << here doc

*/


#include "ft_defines.h"
#include "minishell.h"

int run_builtin(int fd_in, int fd_out, t_command *cmd)
{
    if (ft_strcmp(cmd->name, "echo") == 0)
        return (ft_echo(cmd));
    if (ft_strcmp(cmd->name, "cd") == 0)
        return (ft_cd(cmd));
    if (ft_strcmp(cmd->name, "pwd") == 0)
        return (ft_pwd(cmd));
    if (ft_strcmp(cmd->name, "export") == 0)
        return (ft_export(cmd));
    if (ft_strcmp(cmd->name, "unset") == 0)
        return (ft_unset(cmd));
    if (ft_strcmp(cmd->name, "env") == 0)
        return (ft_env(cmd));
    if (ft_strcmp(cmd->name, "exit") == 0)
        return (ft_exit(cmd));
    return (0);
}



int execute_command(t_minishell *mnsh, t_command *cmd)
{
    if (cmd->type == CMD_BUILTIN)
    {
        return (run_builtin(cmd->fd_in, cmd->fd_out, cmd));
    }
    else if (cmd->type == CMD_EXTERNAL)
    {
        

    }
    else if (cmd->type == CMD_ASSIGNMENT)
    {
        // handle variable assignment
        // e.g., VAR=value
        // update mnsh->variables
        // return 0 for success
    }
    else if (cmd->type == CMD_HEREDOC)
    {
        // handle here document
        // e.g., << EOF ... EOF
        // create a temporary file or use a pipe to store the here doc content
        // return 0 for success
    }
    else
    {
        ft_putstr_fd(": command not found: ", 2);
        ft_putstr_fd(cmd->name, 2);
        ft_putstr_fd("\n", 2);
    }
    return (0);
}