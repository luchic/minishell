/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:02:02 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/08 11:19:46 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_subshell(t_tokenstream *ts)
{
	t_subshell *subshell;
	if (!ts_expect(ts, PAREN_OPEN))
		return (NULL);
	t_ast_node *ast_script = parse_script(ts);
	if (!ast_script)
		return (NULL);
	if (!ts_expect(ts, PAREN_CLOSE))
		return (NULL);
	subshell = ft_calloc(1, sizeof(t_subshell));
	if (!subshell)
		return (NULL);
	subshell->script = ast_script;
	t_ast_node *ast_node = create_ast_node(SUBSHELL);
	if (!ast_node)
		return (NULL);
	ast_node->subshell = subshell;
	return (ast_node);
}