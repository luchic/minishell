#include "ft_defines.h"
#include "ft_lexer.h"
#include "ft_parser.h"

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

