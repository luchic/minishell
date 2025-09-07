#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

t_token	*ts_peek(t_tokenstream *ts)
{
	if (!ts || !ts->cur)
		return (NULL);
	return ((t_token *)ts->cur->content);
}

t_token	*ts_advance(t_tokenstream *ts)
{
	t_token	*t;

	t = ts_peek(ts);
	if (ts->cur)
		ts->cur = ts->cur->next;
	return (t);
}

int	ts_match(t_tokenstream *ts, t_token_type type)
{
	t_token	*t;

	t = ts_peek(ts);
	if (t && t->type == type)
		return (1);
	return (0);
}

int	ts_expect(t_tokenstream *ts, t_token_type type)
{
	t_token	*t;

	t = ts_peek(ts);
	if (t && t->type == type)
	{
		ts_advance(ts);
		return (1);
	}
	return (0);
}

t_tokenstream	*ts_clone(t_tokenstream *src)
{
	t_tokenstream	*clone;

	clone = ft_calloc(1, sizeof(t_tokenstream));
	if (!clone)
		return (NULL);
	clone->cur = src->cur;
	return (clone);
}

void	ts_free(t_tokenstream *ts)
{
	if (ts)
		free(ts);
}