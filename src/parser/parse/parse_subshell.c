/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:02:02 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/08 13:29:56 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_subshell(t_tokenstream *ts)
{
	t_subshell	*subshell;
	t_ast_node	*ast_script;
	t_ast_node	*ast_node;

	if (!ts_expect(ts, PAREN_OPEN))
		return (NULL);
	ast_script = parse_script(ts);
	if (!ast_script)
		return (NULL);
	if (!ts_expect(ts, PAREN_CLOSE))
		return (free_ast_tree(ast_script), NULL);
	subshell = ft_calloc(1, sizeof(t_subshell));
	if (!subshell)
		return (free_ast_tree(ast_script), NULL);
	subshell->script = ast_script;
	ast_node = create_ast_node(SUBSHELL);
	if (!ast_node)
		return (free_subshell(subshell), NULL);
	ast_node->subshell = subshell;
	return (ast_node);
}
