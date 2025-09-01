/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:31:55 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 14:02:04 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "ft_printer.h"
#include "libft.h"
#include "ft_utils.h"

static int	ft_get_str_len(t_format *cur, char *str)
{
	int	str_len;

	if (cur->flags & FLAG_DOT)
		str_len = ft_min(cur->precision, (int)ft_strlen(str));
	else
		str_len = (int)ft_strlen(str);
	return (str_len);
}

static int	ft_fill_if_zero(t_format *cur, char *str, int fd)
{
	int	str_len;
	int	to_fill;

	str_len = ft_get_str_len(cur, str);
	if (cur->flags & FLAG_ZERO)
		to_fill = ft_max(cur->width, str_len);
	else
		to_fill = str_len;
	if (ft_fillspace(cur->width - to_fill, ' ', fd) == -1)
		return (-1);
	if (cur->flags & FLAG_ZERO && ft_fillspace(to_fill - str_len, '0', fd)
		== -1)
		return (-1);
	if (ft_putnstr_fd(str, str_len, fd) == -1)
		return (-1);
	return (0);
}

static int	print_string_in_prec(t_format *cur, char *str, int fd)
{
	int	str_len;

	str_len = ft_get_str_len(cur, str);
	if (cur->width == 0)
		return (ft_putnstr_fd(str, str_len, fd));
	if (cur->flags & FLAG_MINUS)
	{
		if (ft_putnstr_fd(str, str_len, fd) == -1)
			return (-1);
		if (ft_fillspace(cur->width - str_len, ' ', fd) == -1)
			return (-1);
	}
	else
	{
		if (ft_fill_if_zero(cur, str, fd) == -1)
			return (-1);
	}
	return (ft_max(str_len, cur->width));
}
#if defined(__linux__)

int	print_str(va_list ap, t_format *cur, int fd)
{
	char	*str;

	str = va_arg(ap, char *);
	if (!str && cur->flags & FLAG_DOT && cur->precision < 6)
		str = "";
	else if (!str)
		str = "(null)";
	return (print_string_in_prec(cur, str, fd));
}
#elif defined(__APPLE__)

int	print_str(va_list ap, t_format *cur, int fd)
{
	char	*str;

	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	return (print_string_in_prec(cur, str, fd));
}
#endif