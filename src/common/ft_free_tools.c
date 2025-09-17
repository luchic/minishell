/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:47:12 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/15 22:30:46 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_common.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_redir(void *redir)
{
	t_redirection	*r;

	r = (t_redirection *)redir;
	if (!r)
		return ;
	if (r->value)
		free(r->value);
	free(r);
}


void	free_cmd(t_command *cmd)
{
	int				i;
	t_redirection	*redir;
	t_redirection	*tmp;

	if (!cmd)
		return ;
	if (cmd->name)
		free(cmd->name);
	if (cmd->args)
		free_str_array(cmd->args);
	if (cmd->redirections)
		ft_lstclear(&cmd->redirections, (void *)ft_free_redir);
	if (cmd->assignments)
		ft_lstclear(&cmd->assignments, free);
	free(cmd);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline)
		return ;
	i = 0;
	if (pipeline->commands)
	{
		while (i < pipeline->count)
		{
			free_ast_tree(pipeline->commands[i]);
			i++;
		}
		free(pipeline->commands);
	}
	free(pipeline);
}

void	free_ast_tree(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == COMMAND)
		free_cmd(node->command);
	else if (node->type == PIPELINE)
		free_pipeline(node->pipeline);
	else if (node->type == SUBSHELL)
		free_subshell(node->subshell);
	else if (node->type == LOGICAL)
		free_logical(node->logical);
	free(node);
}
