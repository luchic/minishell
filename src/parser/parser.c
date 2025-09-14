/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:30:11 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/12 13:20:51 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

void set_minishell_to_commands(t_ast_node *node, t_minishell *mnsh)
{
	int i;

	if (!node)
		return ;
	if (node->type == COMMAND && node->command)
		node->command->mnsh = mnsh;
	else if (node->type == PIPELINE && node->pipeline)
	{
		i = -1;
		while (++i < node->pipeline->count)
			set_minishell_to_commands(node->pipeline->commands[i], mnsh);
	}
	else if (node->type == LOGICAL && node->logical)
	{
		set_minishell_to_commands(node->logical->left, mnsh);
		set_minishell_to_commands(node->logical->right, mnsh);
	}
	else if (node->type == SUBSHELL && node->subshell)
	{
		set_minishell_to_commands(node->subshell->script, mnsh);
	}
}

t_ast_node	*run_parser(t_list *tokens, t_minishell *mnsh)
{
	t_tokenstream	ts;
	t_ast_node		*ast;

	ts.cur = tokens;
	ast = parse_script(&ts);
	if (!ast)
		return (NULL);
	if (mnsh)
		set_minishell_to_commands(ast, mnsh);
	return (ast);
}
