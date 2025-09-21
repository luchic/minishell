
#include "lexer.h"

int	is_single(t_quote_status status)
{
	if (status == SINGLE_QUOTED)
		return (1);
	return (0);
}

int	is_double(t_quote_status status)
{
	if (status == DOUBLE_QUOTED)
		return (1);
	return (0);
}

int	is_single_or_double(t_quote_status status)
{
	if (status == SINGLE_QUOTED || status == DOUBLE_QUOTED)
		return (1);
	return (0);
}
