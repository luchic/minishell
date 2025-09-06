/*
check which command type
external: use fork + execve
built-in: call the function directly
assignment: update the variable in mnsh->variables
special: << here doc

*/


#include "ft_defines.h"
#include "minishell.h"

int run_builtin(t_command *cmd)
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
    int	orig_fd_in;
	int	orig_fd_out;

	//backup original fds
	orig_fd_in = dup(STDIN);
	orig_fd_out = dup(STDOUT);
	//handle redirections
	if (cmd->fd_in != STDIN)
	{
		dup2(cmd->fd_in, STDIN);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT)
	{
		dup2(cmd->fd_out, STDOUT);
		close(cmd->fd_out);
	}

	//execute based on command type
	if (cmd->type == CMD_BUILTIN)
    {
        return (run_builtin(cmd));
    }
    else if (cmd->type == CMD_EXTERNAL)
    {
		return (run_external(cmd));
    }
    else if (cmd->type == CMD_ASSIGNMENT)
    {
		// handle variable assignment
		// e.g., VAR=value
		// update mnsh->variables accordingly
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

	//restore original fds
	dup2(orig_fd_in, STDIN);
	dup2(orig_fd_out, STDOUT);
	close(orig_fd_in);
	close(orig_fd_out);
    return (0);
}
