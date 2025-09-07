#include "parser.h"
#include <stdlib.h>


static t_list *create_assignment_list(t_tokenstream *ts)
{
	t_list	*head;
	t_list	*node;
	char	*assignment;

	head = NULL;
	while (ts_match(ts, VARIABLE))
	{
		assignment = ft_strdup(ts_advance(ts)->value);
		if (!assignment)
			return (ft_lstclear(&head, free), NULL);
		node = ft_lstnew(assignment);
		if (!node)
			return (free(assignment), ft_lstclear(&head, free), NULL);
		ft_lstadd_back(&head, node);
	}

	return (head);
}

t_ast_node	*create_assignments_node(t_tokenstream *ts)
{
	t_ast_node	*node;
	t_command	*command;
	t_list		*assignments;

	node = create_ast_node(COMMAND);
	if (!node)
		return (NULL);
	command = create_command(CMD_ASSIGNMENT);
	if (!command)
		return (free(node), NULL);
	assignments = create_assignment_list(ts);
	if (!assignments)
		return (free(node), free(command), NULL);
	command->assignments = assignments;
	node->command = command;
	return (node);
}
