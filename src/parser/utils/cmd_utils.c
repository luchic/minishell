/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:36:57 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/08 10:41:43 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

int	realloc_args(t_command *cmd, int new_size)
{
	char	**new_args;

	new_args = ft_realloc(cmd->args, sizeof(char *) * (new_size - 1),
			sizeof(char *) * new_size);
	if (!new_args)
		return (0);
	cmd->args = new_args;
	return (1);
}

t_command	*create_command(t_cmd_type type)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_command));
	cmd->type = type;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	return (cmd);
}
