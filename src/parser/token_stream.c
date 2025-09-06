#include "ft_lexer.h"
#include "ft_parser.h"

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