/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:56:03 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/24 22:38:22 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	execute_script(t_minishell *mnsh, t_ast_node *script)
{
	int	last_exit_status;

	if (!script)
		return (EXIT_FAILURE);
	if (script->type != COMMAND && script->type != PIPELINE
		&& script->type != LOGICAL && script->type != SUBSHELL)
	{
		return (EXIT_FAILURE);
	}
	last_exit_status = execute_node(mnsh, script);
	mnsh->last_exit_status = last_exit_status;
	return (last_exit_status);
}

int	execute_node(t_minishell *mnsh, t_ast_node *node)
{
	if (!node)
		return (EXIT_FAILURE);
	if (node->type == COMMAND)
	{
		return (execute_command(mnsh, node->command));
	}
	else if (node->type == PIPELINE)
	{
		return (execute_pipeline(mnsh, node->pipeline));
	}
	else if (node->type == LOGICAL)
	{
		return (execute_logical(mnsh, node->logical));
	}
	else if (node->type == SUBSHELL)
	{
		return (execute_subshell(mnsh, node->subshell));
	}
	return (EXIT_FAILURE);
}
