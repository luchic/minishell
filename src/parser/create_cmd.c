
#include "ft_defines.h"
#include "ft_lexer.h"
#include "ft_parser.h"
#include <stdlib.h>

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

// NOTE: For that version only one
t_ast_node	*create_ast_node_assignment(t_token *token)
{
	t_ast_node	*node;
	t_command	*command;

	node = create_ast_node(COMMAND);
	if (!node)
		return (NULL);
	command = create_command(CMD_ASSIGNMENT);
	if (!command)
		return (free(node), NULL);
	command->name = ft_strdup(token->value);
	node->command = command;
	return (node);
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
	{
		i = -1;
		while (cmd->args[++i])
			free(cmd->args[i]);
		free(cmd->args);
	}
	redir = cmd->redirections;
	while (redir)
	{
		tmp = redir->next;
		if (redir->value)
			free(redir->value);
		free(redir);
		redir = tmp;
	}
	free(cmd);
}
