/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tools1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:08:21 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/23 20:37:09 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include <stdlib.h>

void	free_subshell(t_subshell *subshell)
{
	if (subshell)
	{
		if (subshell->script)
			free_ast_tree(subshell->script);
		free(subshell);
	}
}

void	free_logical(t_logical_expression *logic)
{
	if (logic)
	{
		if (logic->left)
			free_ast_tree(logic->left);
		if (logic->right)
			free_ast_tree(logic->right);
		free(logic);
	}
}

void	free_variable(t_var *var)
{
	t_var	*tmp;

	while (var)
	{
		tmp = var;
		var = var->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	free_script(t_script *script)
{
	if (script)
	{
		if (script->nodes)
			free_ast_tree(script->nodes);
		free(script);
	}
}

void	free_stack_minishell(t_minishell *mnsh)
{
	if (!mnsh)
		return ;
	if (mnsh->envp)
	{
		free_str_array(mnsh->envp);
	}
	if (mnsh->script)
	{
		free_script(mnsh->script);
	}
	if (mnsh->variables)
	{
		free_variable(mnsh->variables);
	}
}
