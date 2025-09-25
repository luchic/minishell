
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
			{
				return (EXIT_FAILURE);
			}
		}
		redir_list = redir_list->next;
	}
	return (EXIT_SUCCESS);
}

int	preprocess_heredoc_node(t_ast_node *node)
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
			if (preprocess_heredoc_node(node->pipeline->commands[i]) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
	}
	if (node->type == LOGICAL)
	{
		if (preprocess_heredoc_node(node->logical->left) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (preprocess_heredoc_node(node->logical->right) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	if (node->type == SUBSHELL)
		return (preprocess_heredoc_node(node->subshell->script));
	return (EXIT_SUCCESS);
}
