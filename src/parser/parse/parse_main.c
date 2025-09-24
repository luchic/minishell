/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:01:50 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 15:01:53 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_logical_expression	*create_logical_node(t_tokenstream *ts,
		t_ast_node *left)
{
	t_logical_op	op;

	op = get_logical_op(ts);
	if (op == OP_INVALID)
		return (NULL);
	return (create_logical_expression(op, left, NULL));
}

static t_ast_node	*parse_logical_nodes(t_ast_node *left, t_tokenstream *ts,
		t_minishell *mnsh)
{
	t_logical_expression	*logical;
	t_ast_node				*right;

	while (ts_match(ts, AND) || ts_match(ts, OR))
	{
		logical = create_logical_node(ts, left);
		if (!logical)
			return (free_ast_tree(left), NULL);
		ts_advance(ts);
		if (ts_peek(ts) == NULL)
		{
			msg_unexpected_token(ts_peek(ts));
			set_exit_code(mnsh, SYNTAX_ERROR);
			return (free_logical(logical), NULL);
		}
		ft_log_fd(LOG_INFO, STDERR, "Parsing right side of logical\n");
		right = parse_pipeline(ts, mnsh);
		logical->right = right;
		left = create_ast_node(LOGICAL);
		if (!right || !left)
			return (free_logical(logical), NULL);
		left->logical = logical;
	}
	return (left);
}

t_ast_node	*parse_script(t_tokenstream *ts, t_minishell *mnsh)
{
	t_ast_node	*ast_simple_node;

	ft_log_fd(LOG_INFO, STDERR, "Parsing script\n");
	ast_simple_node = parse_pipeline(ts, mnsh);
	if (!ast_simple_node)
		return (NULL);
	if (ts_match(ts, AND) || ts_match(ts, OR))
		return (parse_logical_nodes(ast_simple_node, ts, mnsh));
	return (ast_simple_node);
}
