/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:30:15 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/17 18:55:43 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

t_logical_expression	*create_logical_expression(t_logical_op op,
		t_ast_node *left, t_ast_node *right)
{
	t_logical_expression	*logical;

	logical = ft_calloc(1, sizeof(t_logical_expression));
	if (!logical)
		return (NULL);
	logical->op = op;
	logical->left = left;
	logical->right = right;
	return (logical);
}
