
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"

int execute_command(t_minishell *mnsh, t_command *cmd)
{
	char	**original_env;
	int		status;

	// assignemnts without command
	if (cmd->assignments && !cmd->name)
		return (handle_assignments(mnsh, cmd->assignments), 0);



	//execute based on command type
	if (cmd->type == CMD_BUILTIN)
    {
        original_env = handle_assignments(mnsh, cmd->assignments);
		status = run_builtin(cmd);
		if (original_env)
		{
			free_array(mnsh->envp);
			mnsh->envp = original_env;
		}
		return (status);
    }
    else if (cmd->type == CMD_EXTERNAL)
		return (run_external(cmd));
    else
        ft_printf_fd(STDERR, ": command not found: %s\n", cmd->name);
    return (0);
}
