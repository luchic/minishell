/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:30:11 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 16:24:13 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*run_parser(t_list *tokens, t_minishell *mnsh)
{
	t_tokenstream	ts;
	t_ast_node		*ast;

	ft_log_fd(LOG_INFO, STDERR, "Run parser\n");
	ts.cur = tokens;
	mnsh->parser_status = 0;
	ast = parse_script(&ts, mnsh);
	if (ts.cur != NULL)
	{
		msg_unexpected_token(ts.cur->content);
		set_exit_code(mnsh, SYNTAX_ERROR);
	}
	return (ast);
}
