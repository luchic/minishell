/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:30:11 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/18 22:38:53 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

// void	set_minishell_to_commands(t_ast_node *node, t_minishell *mnsh)
// {
// 	int	i;

// 	if (!node)
// 		return ;
// 	if (node->type == COMMAND && node->command)
// 		node->command->mnsh = mnsh;
// 	else if (node->type == PIPELINE && node->pipeline)
// 	{
// 		i = -1;
// 		while (++i < node->pipeline->count)
// 			set_minishell_to_commands(node->pipeline->commands[i], mnsh);
// 	}
// 	else if (node->type == LOGICAL && node->logical)
// 	{
// 		set_minishell_to_commands(node->logical->left, mnsh);
// 		set_minishell_to_commands(node->logical->right, mnsh);
// 	}
// 	else if (node->type == SUBSHELL && node->subshell)
// 	{
// 		set_minishell_to_commands(node->subshell->script, mnsh);
// 	}
// }

t_ast_node	*run_parser(t_list *tokens, t_minishell *mnsh)
{
	t_tokenstream	ts;
	t_ast_node		*ast;

	ft_log_fd(LOG_INFO, STDERR, "Run parser\n");
	ts.cur = tokens;
	ast = parse_script(&ts, mnsh);
	if (!ast)
	{
		return (NULL);
	}
	return (ast);
}
