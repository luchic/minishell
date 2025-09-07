
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

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
