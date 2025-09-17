/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:02:02 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/17 14:25:31 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_subshell(t_tokenstream *ts, t_minishell *mnsh)
{
	t_subshell	*subshell;
	t_ast_node	*ast_script;
	t_ast_node	*ast_node;

	ft_log_fd(LOG_INFO, STDERR, "Parse subshell\n");
	if (!ts_expect(ts, PAREN_OPEN))
		return (NULL);
	ast_script = parse_script(ts, mnsh);
	if (!ast_script)
		return (NULL);
	if (!ts_match(ts, PAREN_CLOSE))
	{
		msg_unexpected_token(ts_peek(ts));
		set_exit_code(mnsh, SYNTAX_ERROR);
		return (free_ast_tree(ast_script), NULL);
	}
	ts_advance(ts);
	subshell = ft_calloc(1, sizeof(t_subshell));
	if (!subshell)
		return (free_ast_tree(ast_script), NULL);
	subshell->script = ast_script;
	ast_node = create_ast_node(SUBSHELL);
	if (!ast_node)
		return (free_subshell(subshell), NULL);
	return (ast_node->subshell = subshell, ast_node);
}
