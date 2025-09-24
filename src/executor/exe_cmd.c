
# include "minishell.h"
# include "ft_defines.h"
# include "ft_executor.h"
# include "ft_common.h"
# include "expander.h"

static void print_attri_into(t_command *cmd)
{
	ft_log_fd(LOG_INFO, STDERR, "Command fd_in: %d, fd_out: %d\n", cmd->fd_in, cmd->fd_out); ///to delete --- IGNORE ---
	ft_log_fd(LOG_INFO, STDERR, "Command name: %s\n", cmd->name); ///to delete --- IGNORE ---
	ft_log_fd(LOG_INFO, STDERR, "Command type: %d\n", cmd->type); //0 for built-in, 1 for external ///to delete --- IGNORE ---
	int i;
	for (i = 0; cmd->args[i]; i++)  // 确保这个循环正确
	{
	    ft_log_fd(LOG_INFO, STDERR, " Arg[%d]: %s\n", i, cmd->args[i]); ///to delete --- IGNORE ---
	}
	 ft_log_fd(LOG_INFO, STDERR, " Arg[%d]: %s\n", i, cmd->args[i]);
	i = 0;
	if (cmd->redirections)
	{
		for (t_list *dir = cmd->redirections; dir; dir = dir->next)  // 确保这个循环正确
		{
			ft_log_fd(LOG_INFO, STDERR, " Redirection[%d]: type=%d, value=%s\n", i, ((t_redirection *)dir->content)->type, ((t_redirection *)dir->content)->value); ///to delete --- IGNORE ---
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
		ft_log_fd(LOG_INFO, STDERR, " Assignment[%d]: %s=%s\n", j, ((t_var *)var->content)->name, ((t_var *)var->content)->value); ///to delete --- IGNORE ---
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
	int		orig_fds[2];
	int		is_builtin_with_redir;

	//set up defaults
	status = 0;
	orig_fds[0] = -1;
	orig_fds[1] = -1;
	is_builtin_with_redir = 0;
	original_env = NULL;
	should_restore_env = 0;

	// basic checks
	if (!cmd->name && !cmd->assignments)
		return (EXIT_SUCCESS);
	run_variable_expander(cmd);
	run_wildcards_expander(cmd);
	if (cmd->type == CMD_BUILTIN && cmd->redirections)
	{
		is_builtin_with_redir = 1;
		orig_fds[0] = dup(STDIN);
		orig_fds[1] = dup(STDOUT);
		if (orig_fds[0] == -1 || orig_fds[1] == -1)
			return (ft_log_fd(LOG_ERROR, STDERR, "%s", PREFIX, "dup error\n"), EXIT_FAILURE);
	}
	if (handle_redirections(cmd) == EXIT_FAILURE)
	{
		if (is_builtin_with_redir)
		{
			dup2(orig_fds[0], STDIN_FILENO);
			dup2(orig_fds[1], STDOUT_FILENO);
			close(orig_fds[0]);
			close(orig_fds[1]);
		}
        return (EXIT_FAILURE);

	}

	// update cmd->name if cmd->args[0] is different
	if (cmd->args && cmd->args[0])
	{
		if (cmd->name== NULL || ft_strcmp(cmd->name, cmd->args[0]) != 0)
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
	// if no cmd name, but just assignments
	if (!cmd->name && cmd->assignments)
	{
		original_env = handle_assignments(mnsh, cmd->assignments);
		free_str_array(original_env);
		return (EXIT_SUCCESS);
	}

	if (cmd->fd_in == -1)
		cmd->fd_in = STDIN;
	if (cmd->fd_out == -1)
		cmd->fd_out = STDOUT;
		
	print_attri_into(cmd); ///to delete --- IGNORE ---

	update_underscore(mnsh, cmd);

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

	// execute command
	if (cmd->type == CMD_BUILTIN)
		status = run_builtin(cmd);
    else if (cmd->type == CMD_EXTERNAL)
		status = run_external(cmd);
	
	ft_log_fd(LOG_INFO, STDERR, "after run cmd->type: %d, status: %d\n", cmd->type, status); ///to delete --- IGNORE ---

	mnsh->last_exit_status = status;
	if (should_restore_env && original_env)
	{
		free_str_array(mnsh->envp);
		mnsh->envp = original_env;
	}
	ft_log_fd(LOG_INFO, STDERR, "the command %s exit with status: %d\n", cmd->name ? cmd->name : "(null)", status); ///to delete --- IGNORE ---
	
	if (is_builtin_with_redir)
	{
		dup2(orig_fds[0], STDIN_FILENO);
		dup2(orig_fds[1], STDOUT_FILENO);
		close(orig_fds[0]);
		close(orig_fds[1]);
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

	if (cmd->args && cmd->args[0])
	{
		if (cmd->name== NULL || ft_strcmp(cmd->name, cmd->args[0]) != 0)
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


	if (!cmd->name && cmd->assignments)
	{
		original_env = handle_assignments(mnsh, cmd->assignments);
		free_str_array(original_env);
		return (EXIT_SUCCESS);
	}

	if (cmd->assignments)
	{
		original_env = handle_assignments(mnsh, cmd->assignments);
		free_str_array(original_env);
	}

	if (cmd->type == CMD_BUILTIN)
		status = run_builtin(cmd);
    else if (cmd->type == CMD_EXTERNAL)
		status = run_external_no_fork(cmd);

	return (status);
}
