/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:08:21 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/09 21:46:51 by nluchini         ###   ########.fr       */
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
