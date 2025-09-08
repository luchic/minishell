
#include "parser.h"

t_logical_op	get_logical_op(t_tokenstream *ts)
{
	t_tokenstream	*clone;

	clone = ts_clone(ts);
	while (ts_peek(clone))
	{
		if (ts_match(clone, AND))
		{
			ts_free(clone);
			return (OP_AND);
		}
		if (ts_match(clone, OR))
		{
			ts_free(clone);
			return (OP_OR);
		}
		ts_advance(clone);
	}
	ts_free(clone);
	return (OP_INVALID);
}
