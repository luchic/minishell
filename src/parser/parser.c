/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:30:11 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 15:04:50 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*run_parser(t_list *tokens, t_minishell *mnsh)
{
	t_tokenstream	ts;
	t_ast_node		*ast;

	ft_log_fd(LOG_INFO, STDERR, "Run parser\n");
	ts.cur = tokens;
	ast = parse_script(&ts, mnsh);
	return (ast);
}
