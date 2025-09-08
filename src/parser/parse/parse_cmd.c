/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:30:13 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/08 13:30:05 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"

static int	set_command_args(t_command *cmd, t_tokenstream *ts)
{
	t_ast_node	*ast_node;
	int			argc;
	t_token		*arg;

	argc = 0;
	while (ts_match(ts, WORD))
	{
		arg = ts_advance(ts);
		if (realloc_args(cmd, argc + 1) == 0)
			return (free_cmd(cmd), 0);
		cmd->args[argc++] = ft_strdup(arg->value);
		if (!cmd->args[argc - 1])
			return (free_cmd(cmd), 0);
		if (!set_redirection(cmd, ts))
			return (free_cmd(cmd), 0);
	}
	if (!realloc_args(cmd, argc + 1))
		return (free_cmd(cmd), 0);
	cmd->args[argc] = NULL;
	if (!set_redirection(cmd, ts))
		return (free_cmd(cmd), 0);
	return (1);
}

static int	parse_command_fields(t_command *command, t_tokenstream *ts)
{
	t_token	*tok_name;

	if (ts_match(ts, VARIABLE))
		command->assignments = create_assignments_node(ts);
	if (!set_redirection(command, ts))
		return (0);
	if (!ts_match(ts, WORD))
		return (0);
	tok_name = ts_peek(ts);
	command->name = ft_strdup(tok_name->value);
	if (!command->name)
		return (0);
	if (!set_command_args(command, ts))
		return (0);
	if (!set_redirection(command, ts))
		return (0);
	return (1);
}

t_ast_node	*parse_simple_command(t_tokenstream *ts)
{
	t_command	*command;
	t_ast_node	*ast_node;

	command = create_command(CMD_EXTERNAL);
	if (!command)
		return (NULL);
	if (!parse_command_fields(command, ts))
		return (free_cmd(command), NULL);
	ast_node = create_ast_node(COMMAND);
	if (!ast_node)
		return (free_cmd(command), NULL);
	return (ast_node->command = command, ast_node);
}
