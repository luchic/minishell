#include "ft_defines.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

t_ast_node	*run_parser(t_list *tokens, char *input)
{
	t_tokenstream	ts;
	t_ast_node	*ast;

	ts.cur = tokens;
	ast = parse_script(&ts);
	return (ast);
}
