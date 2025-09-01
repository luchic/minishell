/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:23:22 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 13:59:42 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "ft_parser.h"
#include "ft_utils.h"
#include "libft.h"

static size_t	skip_digit(const char *format, t_format *cur)
{
	int		num;
	size_t	i;

	num = ft_atoi(format);
	if (*(format - 1) == '.')
		cur->precision = num;
	else if (*(format - 1) != '%' && *(format - 2) == '.' && *(format
			- 1) == '0')
		cur->precision = num;
	else
		cur->width = num;
	i = 0;
	while (ft_isdigit(format[i]))
		i++;
	return (i);
}

static void	ft_validate_asteriks(const char *format, t_format *cur)
{
	if (*(format - 1) == '.')
	{
		cur->flags |= FLAG_PAST;
	}
	else
	{
		if (cur->flags & FLAG_PAST)
			cur->is_past_reverce = 1;
		cur->flags |= FLAG_DAST;
	}
}

static size_t	parse(const char *format, t_format *cur)
{
	size_t	i;
	char	c;

	i = 0;
	if (!format[i] || !format[i + 1])
		return (0);
	if (format[i] != '%')
		return (ft_set_none(cur));
	ft_reset(cur);
	i++;
	while (ft_is_valid_char(format[i]))
	{
		c = format[i];
		if (ft_istype(c))
			return (ft_set_type(c, cur), i + 1);
		else if (ft_isflag(c))
			cur->flags |= ft_get_flag(&format[i]);
		else if (c == '*')
			ft_validate_asteriks(&format[i], cur);
		else if (ft_isdigit(c))
			i += skip_digit(&format[i], cur) - 1;
		i++;
	}
	ft_validate_format(cur);
	return (i);
}

size_t	ft_parse(const char *format, t_format *cur)
{
	return (parse(format, cur));
}
