
#include "ft_defines.h"
#include "parser.h"

int	is_unexpected_token(t_token_type type, t_token_type *unexpected)
{
	if (type == PIPE || type == AND || type == OR)
	{
		*unexpected = type;
		return (SYNTAX_ERROR);
	}
	return (0);
}

// int is_unexpected_token(t_token_type type, t_token_type *unexpected)
// {
// 	if (type == PIPE || type == AND || type == OR)
// 	{
// 		*unexpected = type;
// 		return (SYNTAX_ERROR);
// 	}
// 	return (0);
// }

int	validate_unexpected_token(t_tokenstream *ts, t_token_type *type)
{
	t_token	*node;
	t_token	*next;

	node = ts_peek(ts);
	if (is_unexpected_token(node->type, type))
		return (SYNTAX_ERROR);
	while (ts_peek(ts) != NULL)
	{
		node = ts_advance(ts);
		next = ts_peek(ts);
		if (is_unexpected_token(node->type, type) && (next == NULL
				|| is_unexpected_token(node->type, type)))
			return (SYNTAX_ERROR);
	}
	return (1);
}

char	*token_type_to_str(t_token_type type)
{
	if (type == PIPE)
		return ("|");
	if (type == AND)
		return ("&&");
	if (type == OR)
		return ("||");
	return ("");
}

int	validate_token(t_tokenstream *ts)
{
	t_token_type	type;
	t_tokenstream	*copy;
	char			*type_str;

	copy = ts_clone(ts);
	if (!copy || !copy->cur)
		return (0);
	if (validate_unexpected_token(copy, &type) == SYNTAX_ERROR)
	{
		type_str = token_type_to_str(type);
		ft_printf_fd(STDERR, "%s: %s `%s'\n", PREFIX, UNEXPECTED_TOKEN,
			type_str);
		return (ts_free(copy), SYNTAX_ERROR);
	}
	ts_free(copy);
	return (0);
}

int	validate(t_tokenstream *ts)
{
	// if (validate_token(ts) == SYNTAX_ERROR)
	// 	return (SYNTAX_ERROR);
	return (0);
}