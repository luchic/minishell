/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:42:04 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/08 13:29:52 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ts_free(t_tokenstream *ts)
{
	if (ts)
		free(ts);
}
