/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:44:39 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 15:02:00 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	realloc_pipe(t_pipeline *pipeline, int new_size)
{
	t_ast_node	**new_commands;

	new_commands = ft_realloc(pipeline->commands, sizeof(t_ast_node *)
			* (new_size - 1), sizeof(t_ast_node *) * new_size);
	if (!new_commands)
		return (0);
	pipeline->commands = new_commands;
	return (1);
}

static t_pipeline	*init_pipeline(void)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	ft_bzero(pipeline, sizeof(t_pipeline));
	return (pipeline);
}

static int	parse_pipe_command_list(t_pipeline *pipeline, t_ast_node *first_cmd,
		t_tokenstream *ts, t_minishell *mnsh)
{
	t_ast_node	*ast_node;

	if (!realloc_pipe(pipeline, pipeline->count + 1))
		return (free_ast_tree(first_cmd), 0);
	pipeline->commands[pipeline->count++] = first_cmd;
	while (ts_expect(ts, PIPE))
	{
		if (ts_peek(ts) == NULL)
		{
			msg_unexpected_token_type(PIPE);
			set_exit_code(mnsh, SYNTAX_ERROR);
			return (0);
		}
		if (ts_match(ts, PAREN_OPEN))
			ast_node = parse_subshell(ts, mnsh);
		else
			ast_node = parse_simple_command(ts, mnsh);
		if (!ast_node)
			return (0);
		if (!realloc_pipe(pipeline, pipeline->count + 1))
			return (free_ast_tree(ast_node), 0);
		pipeline->commands[pipeline->count++] = ast_node;
	}
	return (1);
}

t_ast_node	*parse_pipeline(t_tokenstream *ts, t_minishell *mnsh)
{
	t_pipeline	*pipeline;
	t_ast_node	*ast_node_pipeline;
	t_ast_node	*ast_simple_node;

	ft_log_fd(LOG_INFO, STDERR, "Parse pipeline\n");
	if (ts_match(ts, PAREN_OPEN))
		ast_simple_node = parse_subshell(ts, mnsh);
	else
		ast_simple_node = parse_simple_command(ts, mnsh);
	if (!ast_simple_node)
		return (NULL);
	if (!ts_match(ts, PIPE))
		return (ast_simple_node);
	pipeline = init_pipeline();
	if (!pipeline)
		return (free_ast_tree(ast_simple_node), NULL);
	if (!parse_pipe_command_list(pipeline, ast_simple_node, ts, mnsh))
		return (free_pipeline(pipeline), NULL);
	ast_node_pipeline = create_ast_node(PIPELINE);
	if (!ast_node_pipeline)
		return (free_pipeline(pipeline), NULL);
	ast_node_pipeline->pipeline = pipeline;
	ft_log_fd(LOG_INFO, STDERR, "Pipeline with %d commands\n", pipeline->count);
	return (ast_node_pipeline);
}
