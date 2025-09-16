/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:55:06 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/16 18:56:10 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defines.h"
#include "parser.h"

static int	is_variable_name(char *name)
{
	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	name++;
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

int	is_assignment(t_tokenstream *ts)
{
	t_tokenstream	*clone;
	t_token			*token;

	clone = ts_clone(ts);
	if (!clone)
		return (0);
	token = ts_advance(clone);
	if (!token || token->type != WORD || token->quote_status != UNQUOTED
		|| token->is_space_after)
		return (ts_free(clone), 0);
	if (!is_variable_name(token->value))
		return (ts_free(clone), 0);
	token = ts_advance(clone);
	if (!token || token->type != WORD || ft_strcmp(token->value, "=") != 0
		|| token->quote_status != UNQUOTED)
		return (ts_free(clone), 0);
	ts_free(clone);
	return (1);
}

t_assignment	*allocate_assignment(void)
{
	t_assignment	*assignment;

	assignment = ft_calloc(1, sizeof(t_assignment));
	return (assignment);
}