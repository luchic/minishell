/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_assignments_and_run.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:43:07 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/29 17:31:41 by nluchini         ###   ########.fr       */
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
	int		should_restore;

	should_restore = (cmd->type == CMD_EXTERNAL);
	if (cmd->type == CMD_BUILTIN && !restore_check(cmd))
		should_restore = 0;
	if (cmd->assignments)
	{
		mnsh->restored = handle_assignments(mnsh, cmd->assignments);
	}
	update_underscore(mnsh, cmd);
	*status = run_func(cmd);
	ft_printf("Command exited with status: %d\n", *status);
	if (should_restore && mnsh->restored)
	{
		free_str_array(mnsh->envp);
		mnsh->envp = mnsh->restored;
		mnsh->restored = NULL;
	}
	else if (mnsh->restored)
	{
		free_str_array(mnsh->restored);
		mnsh->restored = NULL;
	}
}
