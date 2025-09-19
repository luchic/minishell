
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"
# include "expander.h"

static void print_attri_into(t_command *cmd)
{
	ft_log_fd(LOG_DEBUG, STDERR, "Command fd_in: %d, fd_out: %d\n", cmd->fd_in, cmd->fd_out); ///to delete --- IGNORE ---
	ft_log_fd(LOG_DEBUG, STDERR, "Command name: %s\n", cmd->name); ///to delete --- IGNORE ---
	ft_log_fd(LOG_DEBUG, STDERR, "Command type: %d\n", cmd->type); //0 for built-in, 1 for external ///to delete --- IGNORE ---
	int i;
	for (i = 0; cmd->args[i]; i++)  // 确保这个循环正确
	{
	    ft_log_fd(LOG_DEBUG, STDERR, " Arg[%d]: %s\n", i, cmd->args[i]); ///to delete --- IGNORE ---
	}
	 ft_log_fd(LOG_DEBUG, STDERR, " Arg[%d]: %s\n", i, cmd->args[i]);
	i = 0;
	if (cmd->redirections)
	{
		for (t_list *dir = cmd->redirections; dir; dir = dir->next)  // 确保这个循环正确
		{
			ft_log_fd(LOG_DEBUG, STDERR, " Redirection[%d]: type=%d, value=%s\n", i, ((t_redirection *)dir->content)->type, ((t_redirection *)dir->content)->value); ///to delete --- IGNORE ---
			i++;
		}
	}
	else
	{
		ft_log_fd(LOG_INFO, STDERR, " No redirections\n"); ///to delete --- IGNORE ---
	}
	if (!cmd->assignments)
	{
		ft_log_fd(LOG_INFO, STDERR, " No assignments\n"); ///to delete --- IGNORE ---
		return ;
	}
	int j = 0;
	for (t_list *var = cmd->assignments; var; var = var->next)  // 确保这个循环正确
	{
		ft_log_fd(LOG_DEBUG, STDERR, " Assignment[%d]: %s=%s\n", j, ((t_var *)var->content)->name, ((t_var *)var->content)->value); ///to delete --- IGNORE ---
		j++;
	}
} 




static void update_underscore(t_minishell *mnsh, t_command *cmd)
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
	if (underscore_var)
	{
		update_env_var(underscore_var, &(mnsh->envp));
		free(underscore_var);
	}
	free(cmd_path);
	return ;
}


 static int	restore_check(t_command *cmd)
{
	if (ft_strcmp(cmd->name, "export") == 0 || ft_strcmp(cmd->name, "unset") == 0 || ft_strcmp(cmd->name, "cd") == 0)
		return (0);
	return (1);
}

int execute_command(t_minishell *mnsh, t_command *cmd)
{
	char	**original_env;
	int		status;
	int		should_restore_env;

	status = 0;
	if (!cmd->name && !cmd->assignments)
		return (EXIT_SUCCESS);

	run_variable_expander(cmd);
	run_wildcards_expander(cmd);

	if (!cmd->name && cmd->assignments)
	{
		original_env = handle_assignments(mnsh, cmd->assignments);
		free_str_array(original_env);
		return (EXIT_SUCCESS);
	}

	if (handle_redirections(cmd) == EXIT_FAILURE)
	{
		print_attri_into(cmd); ///to delete --- IGNORE ---
		ft_log_fd(LOG_ERROR, STDERR, "Failed to handle redirections for command: %s\n", cmd->name ? cmd->name : "(null)"); ///to delete --- IGNORE ---
		status = EXIT_FAILURE;
	}

	if (cmd->fd_in == -1)
		cmd->fd_in = STDIN;
	if (cmd->fd_out == -1)
		cmd->fd_out = STDOUT;
		
	print_attri_into(cmd); ///to delete --- IGNORE ---

	update_underscore(mnsh, cmd);

	should_restore_env = 0;
	if (cmd->assignments)
	{
		if (cmd->type == CMD_BUILTIN)
			should_restore_env = restore_check(cmd);
		else if (cmd->type == CMD_EXTERNAL)
			should_restore_env = 1;
	}

	original_env = handle_assignments(mnsh, cmd->assignments);
	if (!should_restore_env && original_env)
	{
		free_str_array(original_env);
		original_env = NULL;
	}

	if (cmd->type == CMD_BUILTIN)
		status = run_builtin(cmd);
    else if (cmd->type == CMD_EXTERNAL)
		status = run_external(cmd);

	mnsh->last_exit_status = status;
	if (should_restore_env && original_env)
	{
		free_str_array(mnsh->envp);
		mnsh->envp = original_env;
	}
	return (status);
}

int	execute_command_pipeline(t_minishell *mnsh, t_command *cmd)
{
	int		status;
	char	**original_env;

	status = 0;

	run_variable_expander(cmd);
	run_wildcards_expander(cmd);
	

	if (cmd->assignments && !cmd->name)
	{
		original_env = handle_assignments(mnsh, cmd->assignments);
		free_str_array(original_env);
		return (EXIT_SUCCESS);
	}

	if (handle_redirections(cmd) == EXIT_FAILURE)
	{
		ft_log_fd(LOG_ERROR, STDERR, "Failed to handle redirections for command: %s\n", cmd->name ? cmd->name : "(null)"); ///to delete --- IGNORE ---
		status = EXIT_FAILURE;
	}

	ft_log_fd(LOG_DEBUG, STDERR, "After handling redirections:\n"); ///to delete --- IGNORE ---
	ft_log_fd(LOG_INFO, STDERR, " cmd->fd_in: %d, cmd->fd_out: %d\n", cmd->fd_in, cmd->fd_out); ///to delete --- IGNORE ---

	if (cmd->fd_in == -1)
		cmd->fd_in = STDIN;
	if (cmd->fd_out == -1)
		cmd->fd_out = STDOUT;

	print_attri_into(cmd); ///to delete --- IGNORE ---
	update_underscore(mnsh, cmd);

	ft_log_fd(LOG_INFO, STDERR, "Executing command in pipeline: %s\n", cmd->name ? cmd->name : "(null)"); ///to delete --- IGNORE ---
	

	original_env = handle_assignments(mnsh, cmd->assignments);
	free_str_array(original_env);
	original_env = NULL;


	if (cmd->type == CMD_BUILTIN)
		status = run_builtin(cmd);
    else if (cmd->type == CMD_EXTERNAL)
		status = run_external_no_fork(cmd);

	mnsh->last_exit_status = status;

	return (status);
}
