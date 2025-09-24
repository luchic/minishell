
#include "expander.h"
#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	restore_check(t_command *cmd)
{
	if (ft_strcmp(cmd->name, "export") == 0 || ft_strcmp(cmd->name,
			"unset") == 0 || ft_strcmp(cmd->name, "cd") == 0)
		return (0);
	return (1);
}

void	close_previous_fd(int fd_to_close)
{
	if (fd_to_close != STDIN_FILENO && fd_to_close != STDOUT_FILENO
		&& fd_to_close != -1)
	{
		close(fd_to_close);
	}
}

int	preprocess_cmd(t_command *cmd)
{
	run_variable_expander(cmd);
	run_wildcards_expander(cmd);
	if (cmd->args && cmd->args[0])
	{
		if (cmd->name == NULL || ft_strcmp(cmd->name, cmd->args[0]) != 0)
		{
			free(cmd->name);
			cmd->name = ft_strdup(cmd->args[0]);
			if (!cmd->name)
				return (EXIT_FAILURE);
		}
	}
	else if (cmd->name)
	{
		free(cmd->name);
		cmd->name = NULL;
	}
	return (EXIT_SUCCESS);
}

int	execute_dispatcher(t_command *cmd, int in_pipeline)
{
	if (cmd->type == CMD_BUILTIN)
		return (run_builtin(cmd));
	else if (cmd->type == CMD_EXTERNAL)
	{
		if (in_pipeline)
			return (run_external_no_fork(cmd));
		else
			return (run_external(cmd));
	}
	return (EXIT_SUCCESS);
}
