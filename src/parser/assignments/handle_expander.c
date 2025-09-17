/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:56:24 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/17 10:11:57 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_common.h"
#include "parser.h"

int	handle_expander_if_need(int size, t_token *token, t_assignment *assignment)
{
	char	*value;
	char	*var_pos;

	if (token->quote_status == SINGLE_QUOTED)
		return (0);
	value = token->value;
	if (!value)
		return (0);
	var_pos = ft_strchr_not_escaped(value, '$');
	while (var_pos)
	{
		if (handle_var(size, var_pos, token, &assignment->expand) == -1)
			return (-1);
		var_pos = ft_strchr_not_escaped(var_pos + 1, '$');
	}
	return (1);
}
