/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:23:26 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 14:00:26 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "ft_printer.h"
#include "libft.h"
#include "ft_utils.h"

static int	print_char(va_list ap, t_format *cur, int fd)
{
	char	c;

	c = (char)va_arg(ap, int);
	if (cur->width == 0)
		return (ft_putchar_fd(c, fd));
	if (cur->flags & FLAG_MINUS)
	{
		if (ft_putchar_fd(c, fd) == -1)
			return (-1);
		if (ft_fillspace(cur->width - 1, ' ', fd) == -1)
			return (-1);
	}
	else
	{
		if (ft_fillspace(cur->width - 1, ' ', fd) == -1)
			return (-1);
		if (ft_putchar_fd(c, fd) == -1)
			return (-1);
	}
	return (cur->width);
}

static int	ft_print_percent(t_format *cur, int fd)
{
	if (!(cur->flags & FLAG_MINUS))
	{
		if (ft_fillspace(cur->width - 1, ' ', fd) == -1)
			return (-1);
	}
	if (ft_putchar_fd('%', fd) == -1)
		return (-1);
	if (cur->flags & FLAG_MINUS)
		if (ft_fillspace(cur->width - 1, ' ', fd) == -1)
			return (-1);
	return (ft_max(cur->width, 1));
}

/**
• %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.
*/

static int	print_format(t_format *cur, va_list ap, int fd)
{
	if (cur->type == CHAR)
		return (print_char(ap, cur, fd));
	else if (cur->type == STR)
		return (print_str(ap, cur, fd));
	else if (cur->type == PTR)
		return (ft_print_ptr(ap, cur, fd));
	else if (cur->type == INT)
		return (ft_print_int(ap, cur, fd));
	else if (cur->type == UINT)
		return (ft_print_unit(ap, cur, fd));
	else if (cur->type == NONE && cur->format == '%')
		return (ft_print_percent(cur, fd));
	return (-1);
}

int	ft_print_format(t_format *cur, va_list ap, int fd)
{
	if (!cur || !ap)
		return (-1);
	ft_asterisk_handler(cur, ap);
	return (print_format(cur, ap, fd));
}
