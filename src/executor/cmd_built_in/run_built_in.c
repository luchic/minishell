/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:44:04 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/25 16:44:05 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	match_built_in(t_command *cmd)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd->name, "echo") == 0)
		status = ft_echo(cmd);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		status = ft_cd(cmd);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		status = ft_pwd(cmd);
	else if (ft_strcmp(cmd->name, "export") == 0)
		status = ft_export(cmd);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		status = ft_unset(cmd);
	else if (ft_strcmp(cmd->name, "env") == 0)
		status = ft_env(cmd);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		status = ft_exit(cmd);
	return (status);
}

int	run_builtin(t_command *cmd)
{
	int			status;
	t_command	tmp_cmd;

	tmp_cmd = *cmd;
	if (tmp_cmd.name && tmp_cmd.args[0][0] == '\0' && tmp_cmd.args[1])
	{
		tmp_cmd.name = cmd->args[1];
		tmp_cmd.args = &cmd->args[1];
	}
	else if (tmp_cmd.name && tmp_cmd.args[0][0] == '\0')
	{
		return (EXIT_SUCCESS);
	}
	status = match_built_in(&tmp_cmd);
	return (status);
}
