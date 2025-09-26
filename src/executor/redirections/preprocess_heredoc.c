/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:51:42 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/26 14:35:58 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "ft_executor.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int	preprocess_heredoc_cmd(t_command *cmd)
{
	t_list	*redir_list;

	if (!cmd || !cmd->redirections)
		return (EXIT_SUCCESS);
	redir_list = cmd->redirections;
	while (redir_list)
	{
		if (((t_redirection *)redir_list->content)->type == REDIR_HEREDOC)
		{
			if (preprocess_heredocs_fds(redir_list->content) != EXIT_SUCCESS)
				return (cmd->mnsh->last_exit_status);
		}
		redir_list = redir_list->next;
	}
	return (EXIT_SUCCESS);
}

int	prep_heredoc_node(t_ast_node *node)
{
	int	i;

	if (!node)
		return (EXIT_SUCCESS);
	if (node->type == COMMAND)
		return (preprocess_heredoc_cmd(node->command));
	if (node->type == PIPELINE)
	{
		i = -1;
		while (++i < node->pipeline->count)
		{
			if (prep_heredoc_node(node->pipeline->commands[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	if (node->type == LOGICAL)
	{
		if (prep_heredoc_node(node->logical->left) == EXIT_FAILURE
			|| prep_heredoc_node(node->logical->right) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (node->type == SUBSHELL)
		return (prep_heredoc_node(node->subshell->script));
	return (EXIT_SUCCESS);
}
