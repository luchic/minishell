/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:58:24 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 14:02:54 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "libft.h"

int	ft_fillspace(int size, char char_to_fill, int fd)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_putchar_fd(char_to_fill, fd) == -1)
			return (-1);
		i++;
	}
	return (ft_max(size, 0));
}

static void	ft_set_width(t_format *cur, va_list ap)
{
	cur->width = va_arg(ap, int);
	if (cur->width < 0)
	{
		cur->flags |= FLAG_MINUS;
		cur->width = (int)(-(cur->width + 1) + 1);
	}
}

static void	ft_set_precision(t_format *cur, va_list ap)
{
	cur->precision = va_arg(ap, int);
	if (cur->precision < 0)
	{
		cur->flags &= ~(FLAG_PAST | FLAG_DOT);
		cur->precision = 0;
	}
}

void	ft_asterisk_handler(t_format *cur, va_list ap)
{
	if (cur->flags & FLAG_DAST && !cur->is_past_reverce)
		ft_set_width(cur, ap);
	else if (cur->flags & FLAG_DAST && cur->is_past_reverce)
		ft_set_precision(cur, ap);
	if (cur->flags & FLAG_PAST && !cur->is_past_reverce)
		ft_set_precision(cur, ap);
	else if (cur->flags & FLAG_PAST && cur->is_past_reverce)
		ft_set_width(cur, ap);
}
