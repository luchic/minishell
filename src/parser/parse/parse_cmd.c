/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:00:29 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 11:37:57 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"

static int	set_cmd_expander(t_command *cmd, t_list **expander, int index)
{
	t_cmd_expander	*node;

	if (!expander || !*expander)
		return (1);
	node = ft_calloc(1, sizeof(t_cmd_expander));
	if (!node)
		return (0);
	node->index = index;
	node->expand = *expander;
	*expander = NULL;
	ft_lstadd_back(&cmd->expander, ft_lstnew(node));
	return (1);
}

static int	set_command_args(t_command *cmd, t_tokenstream *ts)
{
	int		argc;
	t_list	*expander;

	argc = 0;
	expander = NULL;
	while (ts_match(ts, WORD))
	{
		if (realloc_args(cmd, argc + 1) == 0)
			return (0);
		if (set_merged_value((cmd->args + argc), &expander, ts) == -1)
			return (ft_log_fd(LOG_ERROR, STDERR, "Failed to merge tokens\n"),
				ft_lstclear(&expander, free_expander), 0);
		if (!set_cmd_expander(cmd, &expander, argc))
			return (ft_lstclear(&expander, free_expander), 0);
		if (!set_redirection(cmd, ts))
			return (0);
		argc++;
	}
	if (!realloc_args(cmd, argc + 1))
		return (0);
	cmd->args[argc] = NULL;
	return (1);
}

static int	parse_command_fields(t_command *command, t_tokenstream *ts,
		t_minishell *mnsh)
{
	t_token	*tok_name;

	command->mnsh = mnsh;
	if (create_assignments(ts, &command->assignments) == -1)
		return (0);
	if (!set_redirection(command, ts))
		return (0);
	if (!ts_peek(ts))
		return (1);
	if (!ts_match(ts, WORD))
		return (msg_unexpected_token(ts_peek(ts)), mnsh->last_exit_status = 2,
			0);
	tok_name = ts_peek(ts);
	command->name = ft_strdup(tok_name->value);
	if (!command->name)
		return (0);
	if (!set_command_args(command, ts))
		return (ft_log_fd(LOG_ERROR, STDERR,
				"Failed to set command arguments\n"), 0);
	if (!set_redirection(command, ts))
		return (0);
	return (1);
}

t_ast_node	*parse_simple_command(t_tokenstream *ts, t_minishell *mnsh)
{
	t_command	*command;
	t_ast_node	*ast_node;

	ft_log_fd(LOG_INFO, STDERR, "Parse simple command\n");
	command = create_command(CMD_EXTERNAL);
	if (!command)
		return (ft_log_fd(LOG_ERROR, STDERR,
				"Parse simple command: create_command failed\n"), NULL);
	if (!parse_command_fields(command, ts, mnsh))
	{
		if (mnsh->last_exit_status != SYNTAX_ERROR)
			return (ft_log_fd(LOG_ERROR, STDERR,
					"Parse simple command: parse_command_fields failed\n"),
				free_cmd(command), NULL);
	}
	ast_node = create_ast_node(COMMAND);
	if (!ast_node)
		return (ft_log_fd(LOG_ERROR, STDERR,
				"Parse simple command: create_ast_node failed\n"),
			free_cmd(command), NULL);
	if (is_built_in(command->name))
		command->type = CMD_BUILTIN;
	return (ast_node->command = command, ast_node);
}
