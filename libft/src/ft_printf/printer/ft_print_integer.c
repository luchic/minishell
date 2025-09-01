/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:28:45 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 14:01:07 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "ft_printer.h"
#include "ft_utils.h"
#include "libft.h"
/*
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

static int	ft_print_zero_flag(int num, t_format *cur, int fd)
{
	int				nsize;
	int				dopp;
	unsigned int	unum;

	unum = ft_unsigned(num);
	nsize = ft_getsize_unsigned(unum, 10);
	dopp = 0;
	if (num < 0 || cur->flags & (FLAG_PLUS | FLAG_SPACE))
		dopp = 1;
	if (ft_fillspace(cur->width - nsize - dopp, '0', fd) == -1)
		return (-1);
	return (0);
}

static int	ft_print_zero(int num, t_format *cur, int fd)
{
	int				nsize;
	int				res;
	unsigned int	unum;

	unum = ft_unsigned(num);
	nsize = ft_getsize_unsigned(unum, 10);
	if (cur->flags & (FLAG_DOT))
	{
		if (ft_fillspace(cur->precision - nsize, '0', fd) == -1)
			return (-1);
		if (cur->precision == 0 && num == 0)
			return (0);
	}
	if (cur->flags & FLAG_ZERO && !(cur->flags & FLAG_DOT))
	{
		if (ft_print_zero_flag(num, cur, fd) == -1)
			return (-1);
	}
	res = ft_putulnbr_base_fd(unum, "0123456789", fd);
	if (res == -1)
		return (-1);
	return (ft_max(res, cur->precision));
}

static int	ft_print_sign(int num, t_format *cur, int fd)
{
	int		res;
	char	sign;

	sign = ' ';
	if (cur->flags & FLAG_PLUS)
		sign = '+';
	if (num < 0)
		sign = '-';
	if (cur->flags & (FLAG_PLUS | FLAG_SPACE) || num < 0)
	{
		if (ft_putchar_fd(sign, fd) == -1)
			return (-1);
		res = ft_print_zero(num, cur, fd);
		if (res == -1)
			return (-1);
		return (res + 1);
	}
	return (ft_print_zero(num, cur, fd));
}

static int	ft_size_output(int num, t_format *cur)
{
	int	size;
	int	nsize;

	size = 0;
	nsize = ft_getsize_signed((long)num, 10);
	if (cur->flags & (FLAG_PLUS | FLAG_SPACE) && num >= 0)
		size++;
	if (cur->flags & FLAG_DOT && num < 0 && nsize <= cur->precision)
		size++;
	size += ft_max(nsize, cur->precision);
	return (size);
}

int	ft_print_int(va_list ap, t_format *cur, int fd)
{
	int	num;
	int	res;
	int	is_error;
	int	fl;

	num = va_arg(ap, int);
	is_error = 0;
	fl = cur->flags;
	res = ft_size_output(num, cur);
	if (!(fl & FLAG_MINUS) && (!(fl & FLAG_ZERO) || (fl & FLAG_DOT)))
	{
		if ((fl & FLAG_DOT) && cur->precision == 0 && num == 0)
			res--;
		is_error = ft_fillspace(cur->width - res, ' ', fd);
	}
	if (is_error == -1)
		return (-1);
	res = ft_print_sign(num, cur, fd);
	if (res == -1)
		return (-1);
	if ((fl & FLAG_MINUS))
		is_error = ft_fillspace(cur->width - res, ' ', fd);
	if (is_error == -1)
		return (-1);
	return (ft_max(cur->width, res));
}
