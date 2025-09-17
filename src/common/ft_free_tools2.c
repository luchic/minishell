/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:37:19 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/17 20:10:54 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_common.h"
#include "libft.h"
#include <stdlib.h>

void	free_expander(void *param)
{
	t_expander	*expander;

	expander = (t_expander *)param;
	if (!expander)
		return ;
	if (expander->var_name)
		free(expander->var_name);
	free(expander);
}

void	free_cmd_expander(void *param)
{
	t_cmd_expander	*cmd_exp;

	cmd_exp = (t_cmd_expander *)param;
	if (!cmd_exp)
		return ;
	if (cmd_exp->expand)
		ft_lstclear(&cmd_exp->expand, free_expander);
	free(cmd_exp);
}

void	free_assignment(void *param)
{
	t_assignment	*assignment;

	assignment = (t_assignment *)param;
	if (!assignment)
		return ;
	if (assignment->value)
		free(assignment->value);
	if (assignment->expand)
		ft_lstclear(&assignment->expand, free_expander);
	free(assignment);
}
