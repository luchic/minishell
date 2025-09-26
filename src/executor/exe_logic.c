/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:42:22 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/25 16:42:24 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "minishell.h"

int	execute_logical(t_minishell *mnsh, t_logical_expression *logic)
{
	int	left_status;
	int	right_status;

	right_status = 0;
	left_status = execute_node(mnsh, logic->left);
	if (logic->op == OP_AND)
	{
		if (left_status == 0)
			right_status = execute_node(mnsh, logic->right);
		else
			right_status = left_status;
	}
	else if (logic->op == OP_OR)
	{
		if (left_status != 0)
			right_status = execute_node(mnsh, logic->right);
		else
			right_status = left_status;
	}
	return (right_status);
}
