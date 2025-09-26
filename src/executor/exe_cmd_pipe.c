/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:42:07 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/25 16:42:10 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "ft_common.h"
#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	execute_command_pipeline(t_minishell *mnsh, t_command *cmd)
{
	int		status;
	char	**original_env;

	run_variable_expander(cmd);
	run_wildcards_expander(cmd);
	status = EXIT_SUCCESS;
	if (cmd->type == CMD_BUILTIN)
	{
		if (cmd->assignments)
		{
			original_env = handle_assignments(mnsh, cmd->assignments);
			free_str_array(original_env);
		}
		update_underscore(mnsh, cmd);
		status = run_builtin(cmd);
	}
	else
	{
		handle_assignments_and_run(mnsh, cmd, &status, run_external_no_fork);
	}
	free_and_exit(mnsh, status);
	return (status);
}
