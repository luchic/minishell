/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_validator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:58:27 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/10 16:57:30 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "ft_utils.h"

size_t	ft_set_none(t_format *cur)
{
	cur->type = NONE;
	cur->width = 0;
	cur->flags = NO_FLAG;
	return (1);
}

void	ft_reset(t_format *cur)
{
	cur->flags = NO_FLAG;
	cur->format = '\0';
	cur->type = NONE;
	cur->width = 0;
	cur->precision = 0;
	cur->is_past_reverce = 0;
}
#if defined(__linux__)

void	ft_validate_format(t_format *cur)
{
	int	fl;
	int	tp;

	fl = cur->flags;
	tp = cur->type;
	if (cur->format == '%')
	{
		cur->flags = 0;
		cur->width = 0;
		cur->precision = 0;
	}
	if (tp == INT
		&& (fl & (FLAG_MINUS | FLAG_ZERO)) == (FLAG_MINUS | FLAG_ZERO))
		cur->flags &= (~FLAG_ZERO);
	else if (tp == UINT
		&& (fl & (FLAG_MINUS | FLAG_ZERO)) == (FLAG_MINUS | FLAG_ZERO))
		cur->flags &= (~FLAG_ZERO);
	else if (tp == STR)
		cur->flags &= ~(FLAG_ZERO);
}
#elif defined(__APPLE__)

void	ft_validate_format(t_format *cur)
{
	int	fl;
	int	tp;

	fl = cur->flags;
	tp = cur->type;
	if (tp == INT
		&& (fl & (FLAG_MINUS | FLAG_ZERO)) == (FLAG_MINUS | FLAG_ZERO))
		cur->flags &= (~FLAG_ZERO);
	else if (tp == UINT
		&& (fl & (FLAG_MINUS | FLAG_ZERO)) == (FLAG_MINUS | FLAG_ZERO))
		cur->flags &= (~FLAG_ZERO);
	else if (tp == PTR)
		cur->flags &= ~(FLAG_SPACE | FLAG_PLUS);
}
#endif

void	ft_set_type(char c, t_format *cur)
{
	cur->type = ft_get_datatype(c);
	cur->format = c;
	ft_validate_format(cur);
}
