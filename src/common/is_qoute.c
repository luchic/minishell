/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_qoute.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:56:03 by nluchini          #+#    #+#             */
/*   Updated: 2025/09/26 18:56:07 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
