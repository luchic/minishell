/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:29:25 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/24 15:03:48 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_logical_op	get_logical_op(t_tokenstream *ts)
{
	t_tokenstream	*clone;

	clone = ts_clone(ts);
	while (ts_peek(clone))
	{
		if (ts_match(clone, AND))
		{
			ts_free(clone);
			return (OP_AND);
		}
		if (ts_match(clone, OR))
		{
			ts_free(clone);
			return (OP_OR);
		}
		ts_advance(clone);
	}
	ts_free(clone);
	return (OP_INVALID);
}

int	is_built_in(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}
