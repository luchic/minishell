
#include "ft_defines.h"
#include "libft.h"
#include <stdlib.h>

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_cmd(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->name)
		free(cmd->name);
	if (cmd->args)
		free_array(cmd->args);
	if (cmd->redirections)
		ft_lstclear(&cmd->redirections, free);
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
			free(pipeline->commands[i]);
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
	{
		free_ast_tree(node->subshell->script);
		free(node->subshell);
	}
	else if (node->type == LOGICAL)
	{
		free_ast_tree(node->logical->left);
		free_ast_tree(node->logical->right);
		free(node->logical);
	}
	free(node);
}
