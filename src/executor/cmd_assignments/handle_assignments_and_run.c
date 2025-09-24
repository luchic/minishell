
#include "expander.h"
#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"


void	update_underscore(t_minishell *mnsh, t_command *cmd)
{
	char	*cmd_path;
	char	*underscore_var;

	if (!cmd || !cmd->name)
		return ;
	cmd_path = NULL;
	if (cmd->type == CMD_BUILTIN)
	{
		cmd_path = ft_strjoin("/usr/bin/", cmd->name);
		if (!cmd_path)
			return ;
	}
	else if (cmd->type == CMD_EXTERNAL)
	{
		cmd_path = get_cmd_path(cmd->name, cmd->mnsh->envp);
		if (!cmd_path)
			cmd_path = ft_strdup(cmd->name);
	}
	if (!cmd_path)
		return ;
	underscore_var = ft_strjoin("_=", cmd_path);
	if (!underscore_var)
		return (free(cmd_path));
	return (update_env_var(underscore_var, &(mnsh->envp)), free(underscore_var),
		free(cmd_path));
}

void	handle_assignments_and_run(t_minishell *mnsh, t_command *cmd,
		int *status, int (*run_func)(t_command *))
{
	char **original_env = NULL;
	int should_restore = (cmd->type == CMD_EXTERNAL);
	
	if (cmd->type == CMD_BUILTIN && !restore_check(cmd))
		should_restore = 0;

	if (cmd->assignments)
	{
		original_env = handle_assignments(mnsh, cmd->assignments);
	}

	update_underscore(mnsh, cmd);

	*status = run_func(cmd);

	if (should_restore && original_env)
	{
		free_str_array(mnsh->envp);
		mnsh->envp = original_env;
	}
	else if (original_env)
	{
		free_str_array(original_env);
	}
}
