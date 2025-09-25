/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_assignments_and_run.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:07 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/25 16:43:09 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

void	update_underscore(t_minishell *mnsh, t_command *cmd)
{
	char	*cmd_path;
	char	*underscore;

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
	underscore = ft_strjoin("_=", cmd_path);
	if (!underscore)
		return (free(cmd_path));
	return (update_env_var(underscore, &(mnsh->envp)), free(underscore),
		free(cmd_path));
}

void	handle_assignments_and_run(t_minishell *mnsh, t_command *cmd,
		int *status, int (*run_func)(t_command *))
{
	char	**original_env;
	int		should_restore;

	original_env = NULL;
	should_restore = (cmd->type == CMD_EXTERNAL);
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
